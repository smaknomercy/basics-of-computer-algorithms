#ifndef LLRB_ops_H
#define LLRB_ops_H

#include "node.h"
#include <stdbool.h>

// Rotates the given node to the left
NodePtr rotateLeft(NodePtr h);

// Rotates the given node to the right
NodePtr rotateRight(NodePtr h);

// Flips the colors of the given node and its children
void flipColors(NodePtr h);

// Check whether a binary tree is a binary search tree
bool isBST(NodePtr root);

#endif