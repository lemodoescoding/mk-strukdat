#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int key, depth;
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

  newNode->depth = 0;
  newNode->key = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

BTreeNode *insertNode(BTreeNode *root, int key, int depth) {
  if (root == NULL) {
    BTreeNode *newNode = createNode(key);
    newNode->depth = depth;

    return newNode;
  }

  if (key < root->key) {
    root->left = insertNode(root->left, key, depth + 1);
  } else if (key > root->key) {
    root->right = insertNode(root->right, key, depth + 1);
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
    bt->root = insertNode(bt->root, key, 1);
    bt->_size++;
  }
}

void updateDepth(BTreeNode *node, int currDepth) {
  if (node == NULL)
    return;

  node->depth = currDepth;
  updateDepth(node->left, currDepth + 1);
  updateDepth(node->right, currDepth + 1);
}

BTreeNode *findMinNode(BTreeNode *node) {
  BTreeNode *currNode = node;
  while (currNode && currNode->left != NULL)
    currNode = currNode->left;

  return currNode;
}

BTreeNode *removeNodeBTree(BTreeNode *root, int value) {
  if (root == NULL)
    return NULL;

  if (value > root->key)
    root->right = removeNodeBTree(root->right, value);
  else if (value < root->key)
    root->left = removeNodeBTree(root->left, value);
  else {

    if (root->left == NULL) {
      BTreeNode *right = root->right;
      free(root);
      return right;
    } else if (root->right == NULL) {
      BTreeNode *left = root->left;
      free(root);
      return left;
    }

    BTreeNode *temp = findMinNode(root->right);
    root->key = temp->key;
    root->right = removeNodeBTree(root->right, temp->key);
  }

  updateDepth(root, root->depth);
  return root;
}

void inorderTraverse(BTreeNode *node) {
  if (node == NULL)
    return;

  inorderTraverse(node->left);
  printf("%d ", node->key);
  inorderTraverse(node->right);
}

void freeTree(BTreeNode *node) {
  if (node == NULL)
    return;

  freeTree(node->right);
  freeTree(node->left);

  free(node);
}

int main() {
  BST bst = {0};
  BST *bt = &bst;
  bt->_size = 0;
  bt->root = NULL;

  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    char cmd[7];
    int add_args = 0;

    scanf("%s", cmd);

    if (strcmp(cmd, "INSERT") == 0 || strcmp(cmd, "DELETE") == 0 ||
        strcmp(cmd, "SEARCH") == 0) {
      scanf(" %d", &add_args);

      if (strcmp(cmd, "INSERT") == 0) {
        insertToBTree(bt, add_args);
        continue;
      }

      if (strcmp(cmd, "DELETE") == 0) {
        if (findInBTree(bt, add_args)) {

          bt->root = removeNodeBTree(bt->root, add_args);
          bt->_size--;
        }
        continue;
      }

      if (strcmp(cmd, "SEARCH") == 0) {
        BTreeNode *searched = findNode(bt->root, add_args);
        if (searched == NULL)
          printf("-1\n");
        else
          printf("%d\n", searched->depth);

        continue;
      }

    } else {
      if (bt->_size == 0) {
        printf("EMPTY");
      } else {

        inorderTraverse(bt->root);
      }

      printf("\n");
    }
  }

  /* insertToBTree(bt, 13); */
  /* insertToBTree(bt, 6); */
  /* insertToBTree(bt, 14); */
  /* insertToBTree(bt, 22); */
  /* insertToBTree(bt, 4); */
  /* insertToBTree(bt, 7); */
  /**/
  /* inorderTraverse(bt->root); */
  /**/
  /* BTreeNode *keyFinded = findNode(bt->root, 7); */
  /* if (keyFinded == NULL) { */
  /*   printf("\nTidak ditemukan\n"); */
  /* } else { */
  /**/
  /*   printf("\nKey ditemukan: %d (Ada dalam tree)\n\n", keyFinded->key); */
  /* } */
  /**/
  /* insertToBTree(bt, 7); */
  /**/
  /* printf("\n"); */
  /* inorderTraverse(bt->root); */

  freeTree(bt->root);

  return 0;
}
