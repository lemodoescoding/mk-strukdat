#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int _data, _height;
  struct Node *_left, *_right;
} AVLNode;

typedef struct {
  AVLNode *_root;
  size_t _size;
} AVLTree;

int _getHeight(AVLNode *node) { return (node == NULL) ? 0 : node->_height; }

int _getBalanceFactor(AVLNode *node) {
  if (node == NULL)
    return 0;

  return _getHeight(node->_left) - _getHeight(node->_right);
}

int _max(int a, int b) { return (a > b) ? a : b; }

AVLNode *createNode(int data) {
  AVLNode *temp = (AVLNode *)malloc(sizeof(AVLNode));

  if (!temp)
    return NULL;

  temp->_data = data;
  temp->_height = 1;
  temp->_left = temp->_right = NULL;

  return temp;
}

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

AVLNode *avlSearchNode(AVLNode *root, int data, int printorno) {
  if (root == NULL)
    return root;

  if (printorno)
    printf("%d", root->_data);

  if (data < root->_data) {
    if (printorno)
      printf(" ");
    return avlSearchNode(root->_left, data, printorno);
  } else if (data > root->_data) {
    if (printorno)
      printf(" ");
    return avlSearchNode(root->_right, data, printorno);
  } else {
    if (printorno)
      printf("\n");
    return root;
  }
}

bool AVLFindNode(AVLTree *avl, int data, int printorno) {
  AVLNode *temp = avlSearchNode(avl->_root, data, 0);

  if (temp == NULL || temp->_data != data) {
    if (printorno)
      printf("%d not found\n", data);
    return false;
  } else {
    if (printorno) {
      printf("%d found with path: ", data);
      avlSearchNode(avl->_root, data, printorno);
    }
    return true;
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

int InsertToAVL(AVLTree *avl, int data, int printorno) {
  if (AVLFindNode(avl, data, printorno))
    return -1;

  avl->_root = avlInsertNode(avl, avl->_root, data);
  avl->_size++;

  return 1;
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

int RemoveElemAVL(AVLTree *avl, int value, int printorno) {
  if (AVLFindNode(avl, value, printorno)) {
    avl->_root = _remove_AVL(avl->_root, value);
    avl->_size--;

    return 1;
  } else {
    return -1;
  }
}

int main() {
  AVLTree avl = {0}, *p_avl = &avl;
  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    char cmd[11];
    int X = 0;

    scanf("%s %d", cmd, &X);

    if (strcmp(cmd, "INSERT") == 0) {
      if (InsertToAVL(p_avl, X, 0) == 1) {
        printf("%d inserted\n", X);
      } else {
        printf("%d is already in the tree\n", X);
      }
    } else if (strcmp(cmd, "FIND") == 0) {
      AVLFindNode(p_avl, X, 1);
    } else if (strcmp(cmd, "DELETE") == 0) {
      if (RemoveElemAVL(p_avl, X, 0) == 1) {
        printf("%d deleted\n", X);
      } else {
        printf("%d is not found in the tree\n", X);
      }
    }
  }
}
