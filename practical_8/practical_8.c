#include "BST.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_BSTFloor() {
    // Test case 1: empty tree
    {
       NodePtr head = NULL;
       assert(BSTFloor(head, "A") == NULL);
    }
    
    // Test case 2: tree with one element
    {
       NodePtr head = create_node("M", NULL);
       assert(equal(BSTFloor(head, "M")->key, "M"));
       assert(BSTFloor(head, "L") == NULL);
       assert(equal(BSTFloor(head, "N")->key, "M"));
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 3: tree with one left element
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "G", NULL);
       assert(equal(BSTFloor(head, "G")->key, "G"));
       assert(BSTFloor(head, "F") == NULL);
       assert(equal(BSTFloor(head, "H")->key, "G"));
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 4: tree with one right element
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "T", NULL);
       assert(equal(BSTFloor(head, "M")->key, "M"));
       NodePtr res = BSTFloor(head, "N");
       assert(res != NULL && equal(res->key, "M"));
       assert(equal(BSTFloor(head, "T")->key, "T"));
       assert(equal(BSTFloor(head, "U")->key, "T"));
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 5: tree with multiple left elements
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "K", NULL);
       BSTPut(head, "G", NULL);
       assert(equal(BSTFloor(head, "H")->key, "G"));
       assert(equal(BSTFloor(head, "K")->key, "K"));
       assert(BSTFloor(head, "E") == NULL);
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 6: tree with multiple right elements
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "P", NULL);
       BSTPut(head, "T", NULL);
       BSTPut(head, "W", NULL);
       assert(equal(BSTFloor(head, "Q")->key, "P"));
       assert(equal(BSTFloor(head, "T")->key, "T"));
       assert(equal(BSTFloor(head, "X")->key, "W"));
       assert(BSTFloor(head, "L") == NULL);
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 7: tree with one left and one right element
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "G", NULL);
       BSTPut(head, "T", NULL);
       assert(equal(BSTFloor(head, "H")->key, "G"));
       assert(equal(BSTFloor(head, "M")->key, "M"));
       assert(equal(BSTFloor(head, "S")->key, "M"));
       assert(equal(BSTFloor(head, "T")->key, "T"));
       assert(equal(BSTFloor(head, "U")->key, "T"));
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 8: tree when we go right multiple times
    {
       NodePtr head = create_node("A", NULL);
       BSTPut(head, "C", NULL);
       BSTPut(head, "E", NULL);
       BSTPut(head, "G", NULL);
       assert(equal(BSTFloor(head, "F")->key, "E"));
       assert(equal(BSTFloor(head, "B")->key, "A"));
       assert(equal(BSTFloor(head, "H")->key, "G"));
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 9: tree when we go left multiple times
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "K", NULL);
       BSTPut(head, "I", NULL);
       BSTPut(head, "G", NULL);
       assert(equal(BSTFloor(head, "H")->key, "G"));
       assert(equal(BSTFloor(head, "J")->key, "I"));
       assert(equal(BSTFloor(head, "L")->key, "K"));
       assert(equal(BSTFloor(head, "M")->key, "M"));
       assert(BSTFloor(head, "F") == NULL);
       BSTDestroy(head); // Free allocated memory
    }
    
    // Test case 10: tree when we go left and right multiple times
    {
       NodePtr head = create_node("M", NULL);
       BSTPut(head, "G", NULL);
       BSTPut(head, "T", NULL);
       BSTPut(head, "D", NULL);
       BSTPut(head, "I", NULL);
       BSTPut(head, "W", NULL);
       BSTPut(head, "H", NULL);
       assert(equal(BSTFloor(head, "E")->key, "D"));
       assert(equal(BSTFloor(head, "F")->key, "D"));
       assert(equal(BSTFloor(head, "H")->key, "H"));
       assert(equal(BSTFloor(head, "J")->key, "I"));
       NodePtr res = BSTFloor(head, "S");
       assert(res != NULL && equal(res->key, "M"));
       BSTDestroy(head); // Free allocated memory
    }
    
    // Completed test case: some random tree with at least 6 nodes
    {
        NodePtr head = create_node("S", 0);
        BSTPut(head, "S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "P", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);

        BSTPrint(head);

        assert(equal(BSTFloor(head, "Q")->key, "P"));
        assert(equal(BSTFloor(head, "H")->key, "H"));
        assert(equal(BSTFloor(head, "K")->key, "H"));
        assert(equal(BSTFloor(head, "Y")->key, "X"));

        BSTDestroy(head); // Free allocated memory
    }
    
    {
        NodePtr head = create_node("D", 0);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);

        assert(BSTFloor(head, "A") == NULL);

        BSTDestroy(head); // Free allocated memory
    }
    
    printf("All BSTFloor tests passed.\n");
}

void test_BSTDeleteMin() {
    {
        // Test case 1: Deleting min from an empty tree should return NULL.
        NodePtr head = NULL;
        assert(BSTDeleteMin(head) == NULL);
        BSTDestroy(head); // Free allocated memory
    }

    {
        // Test case 2: Deleting the only node in the tree should return NULL.
        NodePtr head = create_node("D", NULL);
        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == NULL);
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 3: Deleting the min node from a left-skewed tree should update the root.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == head);
        assert(BSTSize(new_head) == 2);
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 4: Deleting the root node when it is the minimum should update root to its
        // right child.
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "B"));
        assert(BSTSize(new_head) == 2);
        assert(equal(new_head->right->key, "C"));
        assert(new_head->left == NULL);
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 5: Deleting the leftmost node in a tree with both left and right subtrees.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "F", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "D"));
        assert(BSTSize(new_head) == 3);
        assert(equal(new_head->left->key, "C"));
        assert(equal(new_head->right->key, "F"));
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 6: Deleting the leftmost node from a balanced tree should update the left
        // child.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "F", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "D"));
        assert(BSTSize(new_head) == 3);
        assert(equal(new_head->left->key, "C"));
        assert(equal(new_head->right->key, "F"));
        BSTDestroy(new_head); // Free allocated memory
    }

    // Optionally print a message if the test passes
    printf("Test passed: Minimum key deleted successfully.\n");
}

int main() {
    test_BSTFloor();
    test_BSTDeleteMin();
    
    printf("All tests passed!\n");

    return 0;
}
