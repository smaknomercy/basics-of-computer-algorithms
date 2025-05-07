#include "BST.h"
#include <assert.h>

NodePtr rotateLeft(NodePtr h) {
  assert(isRed(h->right)); 
  NodePtr x = h->right;     
  h->right = x->left;       
  x->left = h;              
  x->color = h->color;      
  h->color = RED;           
  return x;                 
}

NodePtr rotateRight(NodePtr h) {
  assert(isRed(h->left));
  NodePtr x = h->left;    
  h->left = x->right;     
  x->right = h;           
  x->color = h->color;    
  h->color = RED;         
  return x;               
}

void flipColors(NodePtr h) {
  assert(!isRed(h));      
  assert(isRed(h->left)); 
  assert(isRed(h->right));

  h->color = RED;          
  h->left->color = BLACK;  
  h->right->color = BLACK; 
}

// t2
static bool isBSTrecursive(NodePtr node, NodePtr *prev) {
  if (node == NULL) return true;

  if (!isBSTrecursive(node->left, prev))
      return false;

  if (*prev != NULL && strcmp(node->key, (*prev)->key) < 0)
      return false;

  *prev = node;

  return isBSTrecursive(node->right, prev);
}

bool isBST(NodePtr root) {
  NodePtr prev = NULL;
  return isBSTrecursive(root, &prev);
}