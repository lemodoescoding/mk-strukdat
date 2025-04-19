#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  struct Node *left;
  struct Node *right;
};

typedef struct Node BTreeNode;

typedef struct bst_t {
  BTreeNode *root;
  unsigned int _size;
} BST;

BTreeNode *createNode(int data) {
  BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));

  if (!newNode)
    return NULL;

  newNode->key = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

BTreeNode *insertNode(BTreeNode *root, int key) {
  if (root == NULL) {
    return createNode(key);
  }

  if (key < root->key) {
    root->left = insertNode(root->left, key);
  } else if (key > root->key) {
    root->right = insertNode(root->right, key);
  }

  return root;
}

BTreeNode *findNode(BTreeNode *root, int key) {
  if (root == NULL)
    return NULL;

  if (key < root->key) {
    return findNode(root->left, key);
  } else if (key > root->key) {
    return findNode(root->right, key);
  }

  return root;
}

bool findInBTree(BST *bt, int key) {
  BTreeNode *temp = findNode(bt->root, key);
  if (temp == NULL || temp->key != key)
    return false;
  return true;
}

void insertToBTree(BST *bt, int key) {
  if (bt == NULL) {
    bt->root = NULL;
    bt->_size = 0;
  }

  if (!findInBTree(bt, key)) {
    bt->root = insertNode(bt->root, key);
    bt->_size++;
  }
}

void inorderTraversal(BTreeNode *node) {
  if (node == NULL)
    return;

  inorderTraversal(node->left);
  printf("%d ", node->key);
  inorderTraversal(node->right);
}

void freeTree(BTreeNode *node) {
  if (node == NULL)
    return;

  freeTree(node->right);
  freeTree(node->left);

  free(node);
}

int main() {
  BST bst = {0}, *bt = &bst;

  insertToBTree(bt, 13);
  insertToBTree(bt, 6);
  insertToBTree(bt, 14);
  insertToBTree(bt, 22);
  insertToBTree(bt, 4);
  insertToBTree(bt, 7);

  inorderTraversal(bt->root);

  freeTree(bt->root);
}
