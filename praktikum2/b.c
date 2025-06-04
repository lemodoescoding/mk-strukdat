#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstnode_t {
  int key;
  int count;
  struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
  BSTNode *_root;
  unsigned int _size;
} BST;

BSTNode *__bst__createNode(int value) {
  BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
  newNode->key = value;
  newNode->count = 1;
  newNode->left = newNode->right = NULL;
  return newNode;
}

BSTNode *__bst__incrementCount(BSTNode *root) {
  root->count++;

  return root;
}

BSTNode *__bst__decrementCount(BSTNode *root) {
  root->count--;

  return root;
}

BSTNode *__bst__insert(BSTNode *root, int value) {
  if (root == NULL)
    return __bst__createNode(value);

  if (value < root->key)
    root->left = __bst__insert(root->left, value);
  else if (value > root->key)
    root->right = __bst__insert(root->right, value);

  return root;
}

BSTNode *__bst__decrement(BSTNode *root, int value) {
  if (value < root->key)
    root->left = __bst__decrement(root->left, value);
  else if (value > root->key)
    root->right = __bst__decrement(root->right, value);
  else
    root = __bst__decrementCount(root);

  return root;
}

BSTNode *__bst__increment(BSTNode *root, int value) {
  if (value < root->key)
    root->left = __bst__increment(root->left, value);
  else if (value > root->key)
    root->right = __bst__increment(root->right, value);
  else
    root = __bst__incrementCount(root);

  return root;
}

BSTNode *__bst__search(BSTNode *root, int value) {
  while (root != NULL) {
    if (value < root->key)
      root = root->left;
    else if (value > root->key)
      root = root->right;
    else
      return root;
  }
  return root;
}

BSTNode *__bst__findMinNode(BSTNode *node) {
  BSTNode *currNode = node;
  while (currNode && currNode->left != NULL)
    currNode = currNode->left;

  return currNode;
}

BSTNode *__bst__remove(BSTNode *root, int value) {
  if (root == NULL)
    return NULL;

  if (value > root->key)
    root->right = __bst__remove(root->right, value);
  else if (value < root->key)
    root->left = __bst__remove(root->left, value);
  else {

    if (root->left == NULL) {
      BSTNode *rightChild = root->right;
      free(root);
      return rightChild;
    } else if (root->right == NULL) {
      BSTNode *leftChild = root->left;
      free(root);
      return leftChild;
    }

    BSTNode *temp = __bst__findMinNode(root->right);
    root->key = temp->key;
    root->right = __bst__remove(root->right, temp->key);
  }
  return root;
}

void __bst__inorder(BSTNode *root, BST *bs) {
  if (root) {
    __bst__inorder(root->left, bs);

    printf("%d(%d)", root->key, root->count);
    printf(" ");
    __bst__inorder(root->right, bs);
  }
}

void __bst__postorder(BSTNode *root, BST *bs) {
  if (root) {
    __bst__postorder(root->left, bs);
    __bst__postorder(root->right, bs);

    printf("%d(%d)", root->key, root->count);
    printf(" ");
  }
}

void __bst__preorder(BSTNode *root, BST *bs) {
  if (root) {
    if (root != bs->_root)
      printf(" ");
    printf("%d(%d)", root->key, root->count);
    __bst__preorder(root->left, bs);
    __bst__preorder(root->right, bs);
  }
}

void bst_init(BST *bst) {
  bst->_root = NULL;
  bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) { return bst->_root == NULL; }

int bst_findCountNode(BST *bst, int value) {
  BSTNode *temp = __bst__search(bst->_root, value);

  if (temp == NULL)
    return -1;

  if (temp->key == value)
    return temp->count;
  else
    return -1;
}

bool bst_find(BST *bst, int value) {
  BSTNode *temp = __bst__search(bst->_root, value);
  if (temp == NULL)
    return false;

  if (temp->key == value)
    return true;
  else
    return false;
}

void bst_insert(BST *bst, int value) {
  if (!bst_find(bst, value)) {
    bst->_root = __bst__insert(bst->_root, value);
    bst->_size++;
  } else {
    bst->_root = __bst__increment(bst->_root, value);
  }
}

void bst_remove(BST *bst, int value) {
  if (bst_find(bst, value)) {

    if (bst_findCountNode(bst, value) > 1) {
      __bst__decrement(bst->_root, value);
    } else {
      bst->_root = __bst__remove(bst->_root, value);
      bst->_size--;
    }
  }
}

int main() {
  int N;
  BST bst = {0}, *p_bst = &bst;

  scanf("%d", &N);

  char cmds[N][101];
  int cmdsargs[N];

  for (int i = 0; i < N; i++) {
    char cmd[100];
    int X = 0;

    scanf("%s", cmd);
    if (strcmp(cmd, "inorder") == 0) {
    } else if (strcmp(cmd, "preorder") == 0) {
    } else if (strcmp(cmd, "postorder") == 0) {
    } else if (strcmp(cmd, "insert") == 0) {
      scanf(" %d", &X);
    } else if (strcmp(cmd, "remove") == 0) {
      scanf(" %d", &X);
    }

    strcpy(cmds[i], cmd);
    cmdsargs[i] = X;
  }

  for (int i = 0; i < N; i++) {
    if (strcmp(cmds[i], "inorder") == 0) {
      __bst__inorder(p_bst->_root, p_bst);
      printf("\n");
    } else if (strcmp(cmds[i], "preorder") == 0) {
      __bst__preorder(p_bst->_root, p_bst);
      printf("\n");
    } else if (strcmp(cmds[i], "postorder") == 0) {
      __bst__postorder(p_bst->_root, p_bst);
      printf("\n");
    } else if (strcmp(cmds[i], "insert") == 0) {
      bst_insert(p_bst, cmdsargs[i]);
    } else if (strcmp(cmds[i], "remove") == 0) {
      bst_remove(p_bst, cmdsargs[i]);
    }
  }
}
