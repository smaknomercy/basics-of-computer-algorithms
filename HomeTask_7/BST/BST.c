#include "BST.h"
#include "node.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// BSTGet: Retrieve the value associated with key.
Value BSTGet(NodePtr head, Key key) {
    NodePtr x = head;
    while (x != NULL) {
        if (less(key, x->key))
            x = x->left;
        else if (greater(key, x->key))
            x = x->right;
        else
            return x->val;
    }
    return NULL;
}

// BSTPut: Insert key-value pair into BST (update value if key exists).
NodePtr BSTPut(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return createNode(key, val);
    }    
    if (less(key, head->key))
        head->left = BSTPut(head->left, key, val);
    else if (greater(key, head->key))
        head->right = BSTPut(head->right, key, val);
    else
        head->val = val;
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

// BSTFloor: Find the node with the largest key ≤ given key.
NodePtr BSTFloor(NodePtr head, Key key) {
    if (head == NULL)
        return NULL;
    if (equal(key, head->key))
        return head;
    if (less(key, head->key))
        return BSTFloor(head->left, key);
    NodePtr t = BSTFloor(head->right, key);
    return (t != NULL) ? t : head;
}

// BSTSize: Return number of nodes in subtree.
int BSTSize(NodePtr head) {
    return head ? head->count : 0;
}

// Inorder traversal to store nodes in an array.
static void inorderNodes(NodePtr head, NodePtr *arr, int *index) {
    if (head != NULL) {
        inorderNodes(head->left, arr, index);
        arr[(*index)++] = head;
        inorderNodes(head->right, arr, index);
    }
}

// BSTNodes: Returns an array of nodes in sorted order.
NodePtr *BSTNodes(NodePtr head, int *arraySize) {
    if (head == NULL) {
        *arraySize = 0;
        return NULL;
    }
    *arraySize = head->count;
    NodePtr *nodesArray = (NodePtr*)malloc((*arraySize) * sizeof(NodePtr));
    if (!nodesArray) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    int size = 0;
    inorderNodes(head, nodesArray, &size);
    return nodesArray;
}

// Delete the minimum node.
static NodePtr deleteMin(NodePtr head) {
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);
        return rightSubtree;
    }
    head->left = deleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

// BSTDeleteMin: Remove the minimum node.
NodePtr BSTDeleteMin(NodePtr head) {
    if (head == NULL)
        return NULL;
    return deleteMin(head);
}

// Find the node with the minimum key.
static NodePtr min(NodePtr head) {
    while (head->left != NULL)
        head = head->left;
    return head;
}

// BSTDelete: Delete node with given key.
NodePtr BSTDelete(NodePtr head, Key key) {
    if (head == NULL)
        return NULL;
    if (less(key, head->key))
        head->left = BSTDelete(head->left, key);
    else if (greater(key, head->key))
        head->right = BSTDelete(head->right, key);
    else {
        if (head->right == NULL) {
            NodePtr leftSubtree = head->left;
            free(head);
            return leftSubtree;
        }
        if (head->left == NULL) {
            NodePtr rightSubtree = head->right;
            free(head);
            return rightSubtree;
        }
        NodePtr temp = min(head->right);
        head->key = temp->key;
        head->val = temp->val;
        head->right = deleteMin(head->right);
    }
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

// BSTDestroy: Recursively free all nodes.
void BSTDestroy(NodePtr head) {
    if (head == NULL)
        return;
    BSTDestroy(head->left);
    BSTDestroy(head->right);
    free(head);
}

// BSTIterate: In-order traversal calling func() on each node.
void BSTIterate(NodePtr head, void (*func)(NodePtr)) {
    if (head != NULL) {
        BSTIterate(head->left, func);
        func(head);
        BSTIterate(head->right, func);
    }
}

// BSTPrint: In-order print of keys.
void BSTPrint(const NodePtr head) {
    static int depth = 0;
    if (head != NULL) {
        depth++;
        BSTPrint(head->left);
        printf("%s ", head->key);
        BSTPrint(head->right);
        depth--;
    }
    if (depth == 0)
        printf("\n");
}


// BSTCeiling: Find the smallest node such that key is ≤ node->key.
NodePtr BSTCeiling(NodePtr head, Key key) {
    if (head == NULL)
        return NULL;
    if (equal(key, head->key))
        return head;
    if (less(key, head->key)) {
        NodePtr left_ceiling = BSTCeiling(head->left, key);
        if (left_ceiling != NULL)
            return left_ceiling;
        else
            return head;
    }
    return BSTCeiling(head->right, key);
}

// BSTRank: Return the number of nodes with keys strictly less than the given key.
int BSTRank(NodePtr head, Key key) {
    if (head == NULL)
        return 0;
    if (less(key, head->key))
        return BSTRank(head->left, key);
    else if (equal(key, head->key))
        return BSTSize(head->left);
    else
        return 1 + BSTSize(head->left) + BSTRank(head->right, key);
}

// BSTSelect: Return the node with the given 0-indexed rank.
NodePtr BSTSelect(NodePtr head, int k) {
    if (head == NULL)
        return NULL;
    int left_size = BSTSize(head->left);
    if (k < left_size)
        return BSTSelect(head->left, k);
    else if (k == left_size)
        return head;
    else
        return BSTSelect(head->right, k - left_size - 1);
}

// BSTMin: Return the smallest key in the BST.
Key BSTMin(NodePtr head) {
    if (head == NULL)
        return NULL;
    NodePtr min_node = min(head);
    return min_node->key;
}

// BSTMax: Return the largest key in the BST.
Key BSTMax(NodePtr head) {
    if (head == NULL)
        return NULL;
    while (head->right != NULL)
        head = head->right;
    return head->key;
}

// BSTDeleteMax: Remove the node with the maximum key.
NodePtr BSTDeleteMax(NodePtr head) {
    if (head == NULL)
        return NULL;
    if (head->right == NULL) {
        NodePtr leftSubtree = head->left;
        free(head);
        return leftSubtree;
    }
    head->right = BSTDeleteMax(head->right);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

// BSTPrintReverse: Print keys in descending order (reverse in-order).
void BSTPrintReverse(const NodePtr head) {
    static int depth = 0;
    if (head != NULL) {
        depth++;
        BSTPrintReverse(head->right);
        printf("%s ", head->key);
        BSTPrintReverse(head->left);
        depth--;
    }
    if (depth == 0)
        printf("\n");
}

// Returns the height if subtree is balanced, or -1 if not.
static int checkBalanced(NodePtr node) {
    if (node == NULL)
        return 0;  // An empty tree has height 0.

    int leftHeight = checkBalanced(node->left);
    if (leftHeight == -1)
        return -1; // Left subtree is unbalanced.

    int rightHeight = checkBalanced(node->right);
    if (rightHeight == -1)
        return -1; // Right subtree is unbalanced.

    if (abs(leftHeight - rightHeight) > 1)
        return -1; // Current node is unbalanced.

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

// isBalanced: Returns true if the tree is balanced.
bool isBalanced(NodePtr root) {
    return checkBalanced(root) != -1;
}


static NodePtr buildMinBSTFromSorted(
    Key keys[], Value vals[], int lo, int hi
) {
    if (lo > hi) return NULL;

    int mid = lo + (hi - lo) / 2;
    // create a new node for keys[mid]
    NodePtr root = createNode(keys[mid], vals ? vals[mid] : NULL);

    // recursively build the two subtrees
    root->left  = buildMinBSTFromSorted(keys, vals, lo,   mid-1);
    root->right = buildMinBSTFromSorted(keys, vals, mid+1, hi);

    // fix the subtree size
    root->count = 1 
        + (root->left  ? root->left->count  : 0)
        + (root->right ? root->right->count : 0);
    return root;
}

// Public wrapper: n = number of elements in your sorted array
NodePtr BSTFromSortedArray(Key keys[], Value vals[], int n) {
    return buildMinBSTFromSorted(keys, vals, 0, n-1);
}