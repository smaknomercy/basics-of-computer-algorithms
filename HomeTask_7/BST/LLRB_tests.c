#include "LLRB.h"
#include "LLRB_ops.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void test_LLRBPut() {
    NodePtr head = NULL;

    // Keys to insert into the LLRB tree
    char keys[][2] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    // Insert keys into the LLRB tree
    for (int i = 0; i < num_keys; i++) {
        head = LLRBPut(head, keys[i], keys[i]); // key == value
    }

    // Print the tree (optional for visualization)
    printf("Printing BST:\n");
    BSTPrint(head);

    // Assertions to check the structure of the tree
    assert(equal(head->key, "M")); // Root node
    assert(equal(head->left->key, "J"));
    assert(equal(head->right->key, "R"));

    assert(equal(head->left->left->key, "E"));
    assert(equal(head->left->right->key, "L"));
    assert(equal(head->right->left->key, "P"));
    assert(equal(head->right->right->key, "X"));

    assert(equal(head->left->left->left->key, "C"));
    assert(equal(head->left->left->right->key, "H"));
    assert(equal(head->right->right->left->key, "S"));

    assert(equal(head->left->left->left->left->key, "A"));

    // Check the color of connections
    assert(!isRed(head));        // "M" is black
    assert(!isRed(head->left));   // "J" is black
    assert(!isRed(head->right)); // "R" is black

    assert(isRed(head->left->left)); // "E" is red
    assert(!isRed(head->left->right)); // "L" is black

    assert(!isRed(head->right->left));   // "P" is black
    assert(!isRed(head->right->right)); // "X" is black

    assert(!isRed(head->left->left->left));   // "C" is black
    assert(!isRed(head->left->left->right)); // "H" is black

    assert(isRed(head->right->right->left)); // "S" is red

    assert(isRed(head->left->left->left->left)); // "A" is red

    // Clean up
    BSTDestroy(head);

    printf("test_LLRBPut passed.\n");
}


// t1
static void checkRedLinks(NodePtr h) {
    if (h == NULL) return;
    assert(!isRed(h->right));

    if (isRed(h))
        assert(!isRed(h->left));
    checkRedLinks(h->left);
    checkRedLinks(h->right);
}

static int checkBlackHeight(NodePtr h) {
    if (h == NULL)
        return 1;

    int leftBH  = checkBlackHeight(h->left);
    int rightBH = checkBlackHeight(h->right);
    assert(leftBH == rightBH);

    return leftBH + (isRed(h) ? 0 : 1);
}

void test_LLRBProperties() {
    char *keys[] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
    int num_keys = sizeof(keys)/sizeof(keys[0]);
    NodePtr head = NULL;
    for (int i = 0; i < num_keys; i++)
        head = LLRBPut(head, keys[i], keys[i]);

    assert(!isRed(head));

    checkRedLinks(head);

    checkBlackHeight(head);

    BSTDestroy(head);
    printf("test_LLRBProperties passed.\n");
}

void test_LLRBBalance() {
    const int N = 11;
    char keys[N][3];
    for (int i = 0; i < N; i++) {
        keys[i][0] = 'A' + i;
        keys[i][1] = '\0';
    }

    // ascending insert
    NodePtr bstAsc  = NULL;
    NodePtr llrbAsc = NULL;
    for (int i = 0; i < N; i++) {
        bstAsc  = BSTPut (bstAsc,  keys[i], keys[i]);
        llrbAsc = LLRBPut(llrbAsc, keys[i], keys[i]);
    }
    assert(!isBalanced(bstAsc));
    assert( isBalanced(llrbAsc));
    BSTDestroy(bstAsc);
    BSTDestroy(llrbAsc);

    // descending insert
    NodePtr bstDesc  = NULL;
    NodePtr llrbDesc = NULL;
    for (int i = N-1; i >= 0; i--) {
        bstDesc  = BSTPut (bstDesc,  keys[i], keys[i]);
        llrbDesc = LLRBPut(llrbDesc, keys[i], keys[i]);
    }
    assert(!isBalanced(bstDesc));
    assert(isBalanced(llrbDesc));
    BSTDestroy(bstDesc);
    BSTDestroy(llrbDesc);

    printf("test_LLRBBalance passed.\n");
}


static void test_isBST_empty() {
    assert(isBST(NULL));
    printf("test_isBST_empty passed.\n");
}

static void test_isBST_single() {
    NodePtr n = createNode("X", "X");
    assert(isBST(n));
    BSTDestroy(n);
    printf("test_isBST_single passed.\n");
}

static void test_isBST_valid() {
    //     M
    //    / \
    //   C   T
    //  / \
    // A   E   
    NodePtr root = createNode("M","M");
    root->left       = createNode("C","C");
    root->right      = createNode("T","T");
    root->left->left = createNode("A","A");
    root->left->right= createNode("E","E");

    assert(isBST(root));
    BSTDestroy(root);
    printf("test_isBST_valid passed.\n");
}

static void test_isBST_invalid_left() {
    //    M
    //   /
    //  Z
    NodePtr root = createNode("M","M");
    root->left = createNode("Z","Z");

    assert(!isBST(root));
    BSTDestroy(root);
    printf("test_isBST_invalid_left passed.\n");
}

static void test_isBST_invalid_right() {
    //   M
    //    \
    //     A
    NodePtr root = createNode("M","M");
    root->right = createNode("A","A");

    assert(!isBST(root));
    BSTDestroy(root);
    printf("test_isBST_invalid_right passed.\n");
}

int main() {
    test_LLRBPut();
    test_LLRBProperties();
    test_LLRBBalance();

    test_isBST_empty();
    test_isBST_single();
    test_isBST_valid();
    test_isBST_invalid_left();
    test_isBST_invalid_right();

    printf("All tests passed!\n");
    return 0;
}