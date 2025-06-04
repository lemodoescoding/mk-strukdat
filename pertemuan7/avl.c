#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int _data, _height;
  struct Node *_left, *_right;
} AVLNode;

typedef struct {
  AVLNode *_root;
  size_t _size;
} AVLTree;

AVLNode *createNode(int data) {
  AVLNode *temp = (AVLNode *)malloc(sizeof(AVLNode));

  if (!temp)
    return NULL;

  temp->_data = data;
  temp->_height = 1;
  temp->_left = temp->_right = NULL;

  return temp;
}

int _getHeight(AVLNode *node) { return (node == NULL) ? 0 : node->_height; }

int _getBalanceFactor(AVLNode *node) {
  if (node == NULL)
    return 0;

  return _getHeight(node->_left) - _getHeight(node->_right);
}

int _max(int a, int b) { return (a > b) ? a : b; }

AVLNode *avlRightRotate(AVLNode *pivotNode) {
  AVLNode *newParent = pivotNode->_left;
  pivotNode->_left = newParent->_right;
  newParent->_right = pivotNode;

  pivotNode->_height =
      _max(_getHeight(pivotNode->_left), _getHeight(pivotNode->_right)) + 1;
  newParent->_height =
      _max(_getHeight(newParent->_left), _getHeight(newParent->_right)) + 1;

  return newParent;
}

AVLNode *avlLeftRotate(AVLNode *pivotNode) {
  AVLNode *newParent = pivotNode->_right;
  pivotNode->_right = newParent->_left;
  newParent->_left = pivotNode;

  pivotNode->_height =
      _max(_getHeight(pivotNode->_left), _getHeight(pivotNode->_right)) + 1;
  newParent->_height =
      _max(_getHeight(newParent->_left), _getHeight(newParent->_right)) + 1;

  return newParent;
}

AVLNode *leftCaseRotate(AVLNode *node) { return avlRightRotate(node); }
AVLNode *rightCaseRotate(AVLNode *node) { return avlLeftRotate(node); }

AVLNode *leftRightCaseRotate(AVLNode *node) {
  node->_left = avlLeftRotate(node->_left);
  return avlRightRotate(node);
}

AVLNode *rightLeftCaseRotate(AVLNode *node) {
  node->_right = avlRightRotate(node->_right);
  return avlLeftRotate(node);
}

AVLNode *avlSearchNode(AVLNode *root, int data) {
  if (root == NULL)
    return root;

  if (data < root->_data) {
    return avlSearchNode(root->_left, data);
  } else if (data > root->_data) {
    return avlSearchNode(root->_right, data);
  } else {
    return root;
  }
}

AVLNode *avlInsertNode(AVLTree *avl, AVLNode *node, int data) {
  if (node == NULL)
    return createNode(data);

  if (data < node->_data)
    node->_left = avlInsertNode(avl, node->_left, data);
  else if (data > node->_data)
    node->_right = avlInsertNode(avl, node->_right, data);

  node->_height = 1 + _max(_getHeight(node->_left), _getHeight(node->_right));

  int balanceFactor = _getBalanceFactor(node);
  if (balanceFactor > 1 && data < node->_left->_data)
    return leftCaseRotate(node);
  if (balanceFactor > 1 && data > node->_left->_data)
    return leftRightCaseRotate(node);
  if (balanceFactor < -1 && data > node->_right->_data)
    return rightCaseRotate(node);
  if (balanceFactor < -1 && data < node->_right->_data)
    return rightLeftCaseRotate(node);

  return node;
}

bool AVLFindNode(AVLTree *avl, int data) {
  AVLNode *temp = avlSearchNode(avl->_root, data);

  if (temp == NULL || temp->_data != data)
    return false;
  else
    return true;
}

void InsertToAVL(AVLTree *avl, int data) {
  if (AVLFindNode(avl, data))
    return;

  avl->_root = avlInsertNode(avl, avl->_root, data);
  avl->_size++;
}

AVLNode *_findMinNode(AVLNode *node) {
  AVLNode *currNode = node;
  while (currNode && currNode->_left != NULL)
    currNode = currNode->_left;
  return currNode;
}

AVLNode *_remove_AVL(AVLNode *node, int value) {
  if (node == NULL)
    return node;
  if (value > node->_data)
    node->_right = _remove_AVL(node->_right, value);
  else if (value < node->_data)
    node->_left = _remove_AVL(node->_left, value);
  else {
    AVLNode *temp;
    if ((node->_left == NULL) || (node->_right == NULL)) {
      temp = NULL;
      if (node->_left == NULL)
        temp = node->_right;
      else if (node->_right == NULL)
        temp = node->_left;

      if (temp == NULL) {
        temp = node;
        node = NULL;
      } else
        *node = *temp;

      free(temp);
    } else {
      temp = _findMinNode(node->_right);
      node->_data = temp->_data;
      node->_right = _remove_AVL(node->_right, temp->_data);
    }
  }
  if (node == NULL)
    return node;

  node->_height = _max(_getHeight(node->_left), _getHeight(node->_right)) + 1;

  int balanceFactor = _getBalanceFactor(node);

  if (balanceFactor > 1 && _getBalanceFactor(node->_left) >= 0)
    return leftCaseRotate(node);

  if (balanceFactor > 1 && _getBalanceFactor(node->_left) < 0)
    return leftRightCaseRotate(node);

  if (balanceFactor < -1 && _getBalanceFactor(node->_right) <= 0)
    return rightCaseRotate(node);

  if (balanceFactor < -1 && _getBalanceFactor(node->_right) > 0)
    return rightLeftCaseRotate(node);

  return node;
}

void printPostOrder(AVLNode *node) {
  if (node == NULL)
    return;

  printPostOrder(node->_right);
  printPostOrder(node->_left);
  printf("%d ", node->_data);
}

void printPreOrder(AVLNode *node) {
  if (node == NULL)
    return;

  printf("%d ", node->_data);
  printPreOrder(node->_left);
  printPreOrder(node->_right);
}

void printInOrder(AVLNode *node) {
  if (node == NULL)
    return;

  printInOrder(node->_left);
  printf("%d ", node->_data);
  printInOrder(node->_right);
}

void FreeAVLTree(AVLNode *node) {
  if (node == NULL)
    return;

  FreeAVLTree(node->_left);
  FreeAVLTree(node->_right);

  free(node);
}

int main() {
  AVLTree avl = {0}, *p_avl = &avl;
  /**/
  /* InsertToAVL(p_avl, 1); */
  /* InsertToAVL(p_avl, 2); */
  /* InsertToAVL(p_avl, 3); */
  /* InsertToAVL(p_avl, 4); */
  /* InsertToAVL(p_avl, 5); */
  /* InsertToAVL(p_avl, 6); */
  /* InsertToAVL(p_avl, 7); */
  /* InsertToAVL(p_avl, 99); */
  /* InsertToAVL(p_avl, 12); */
  /* InsertToAVL(p_avl, 31); */

  InsertToAVL(p_avl, 20);
  InsertToAVL(p_avl, 15);
  InsertToAVL(p_avl, 30);
  InsertToAVL(p_avl, 17);

  printPostOrder(p_avl->_root);
  printf("\n");

  printPreOrder(p_avl->_root);
  printf("\n");

  printInOrder(p_avl->_root);

  FreeAVLTree(p_avl->_root);
}
