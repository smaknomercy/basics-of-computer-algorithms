#ifndef BST_H
#define BST_H

#include "node.h"
#include <stdbool.h>

/* Basic BST operations already implemented */
typedef Node* NodePtr;

NodePtr BSTPut(NodePtr, Key key, Value val); // Insert key-value pair (replace if key exists)
Value BSTGet(NodePtr, Key key);              // Retrieve value associated with key
NodePtr BSTFloor(NodePtr, Key key);          // Largest key ≤ given key
int BSTSize(NodePtr);                        // Return total nodes in BST
NodePtr *BSTNodes(NodePtr head, int *arraySize); // Get array of nodes in order
NodePtr BSTDeleteMin(NodePtr);               // Delete minimum key node
NodePtr BSTDelete(NodePtr, Key key);         // Delete node with given key
void BSTIterate(NodePtr, void (*func)(NodePtr)); // In-order traversal
void BSTPrint(const NodePtr);                // In-order print
void BSTDestroy(NodePtr);                    // Free BST memory

/* New functions to be implemented */
NodePtr BSTCeiling(NodePtr, Key key);        // Find the smallest key ≥ given key
int BSTRank(NodePtr, Key key);                 // Number of keys < given key
NodePtr BSTSelect(NodePtr root, int k);        // k-th smallest element in BST
Key BSTMin(NodePtr);                         // Find the smallest key in BST
Key BSTMax(NodePtr);                         // Find the largest key in BST
NodePtr BSTDeleteMax(NodePtr root);          // Delete maximum key node
void BSTPrintReverse(const NodePtr);         // Print BST in descending order

bool isBalanced(NodePtr root);

#endif
