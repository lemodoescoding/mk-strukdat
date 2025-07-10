#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode_t {
  int data;
  struct AVLNode_t *left, *right;
  int height;
} AVLNode;

typedef struct AVL_t {
  AVLNode *_root;
  unsigned int _size;
} AVL;

AVLNode *_avl_createNode(int value) {
  AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
  newNode->data = value;
  newNode->height = 1;
  newNode->left = newNode->right = NULL;
  return newNode;
}

AVLNode *_search(AVLNode *root, int value) {
  while (root != NULL) {
    if (value < root->data)
      root = root->left;
    else if (value > root->data)
      root = root->right;
    else
      return root;
  }
  return root;
}

int _getHeight(AVLNode *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

int _max(int a, int b) { return (a > b) ? a : b; }

void printCaseRotation(const char *type, AVLNode *pivot) {
  int modes = 0;
  if (strcmp(type, "left") == 0) {
    modes = 0;
  } else if (strcmp(type, "right") == 0) {
    modes = 1;
  } else if (strcmp(type, "left right") == 0) {
    modes = 2;
  } else if (strcmp(type, "right left") == 0) {
    modes = 3;
  }

  if (modes == 1) {

    printf("Right Case\n");
    printf("PivotNode: %d\n", pivot->data);
    printf("PivotNode->right: %d\n", pivot->right->data);
    printf("PivotNode->right->right: %d\n", pivot->right->right->data);
  } else if (modes == 0) {

    printf("Left Case\n");
    printf("PivotNode: %d\n", pivot->data);
    printf("PivotNode->left: %d\n", pivot->left->data);
    printf("PivotNode->left->left: %d\n", pivot->left->left->data);
  } else if (modes == 2) {
    printf("Left Right Case\n");
    printf("PivotNode: %d\n", pivot->data);
    printf("PivotNode->left: %d\n", pivot->left->data);
    printf("PivotNode->left->right: %d\n", pivot->left->right->data);
  } else if (modes == 3) {
    printf("Right Left Case\n");
    printf("PivotNode: %d\n", pivot->data);
    printf("PivotNode->right: %d\n", pivot->right->data);
    printf("PivotNode->right->left: %d\n", pivot->right->left->data);
  }
}

void printResult(AVLNode *result) {
  printf("\nresult:\n");
  printf("NewNode: %d\n", result->data);
  printf("NewNode->left: %d\n", result->left->data);
  printf("NewNode->right: %d\n", result->right->data);
}

AVLNode *_rightRotate(AVLNode *pivotNode) {

  AVLNode *newParrent = pivotNode->left;
  pivotNode->left = newParrent->right;
  newParrent->right = pivotNode;

  pivotNode->height =
      _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
  newParrent->height =
      _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

  return newParrent;
}

AVLNode *_leftRotate(AVLNode *pivotNode) {

  AVLNode *newParrent = pivotNode->right;
  pivotNode->right = newParrent->left;
  newParrent->left = pivotNode;

  pivotNode->height =
      _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
  newParrent->height =
      _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

  return newParrent;
}

AVLNode *_leftCaseRotate(AVLNode *node) { return _rightRotate(node); }

AVLNode *_rightCaseRotate(AVLNode *node) { return _leftRotate(node); }

AVLNode *_leftRightCaseRotate(AVLNode *node) {
  node->left = _leftRotate(node->left);
  return _rightRotate(node);
}

AVLNode *_rightLeftCaseRotate(AVLNode *node) {
  node->right = _rightRotate(node->right);
  return _leftRotate(node);
}

int _getBalanceFactor(AVLNode *node) {
  if (node == NULL)
    return 0;
  return _getHeight(node->left) - _getHeight(node->right);
}

AVLNode *_insert_AVL(AVL *avl, AVLNode *node, int value) {

  if (node == NULL)
    return _avl_createNode(value);
  if (value < node->data)
    node->left = _insert_AVL(avl, node->left, value);
  else if (value > node->data)
    node->right = _insert_AVL(avl, node->right, value);

  node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));

  int balanceFactor = _getBalanceFactor(node);

  if (balanceFactor > 1 && value < node->left->data) {
    printCaseRotation("left", node);
    AVLNode *result = _leftCaseRotate(node);

    printResult(result);

    return result;
  }

  if (balanceFactor > 1 && value > node->left->data) {
    printCaseRotation("left right", node);
    AVLNode *result = _leftRightCaseRotate(node);

    printResult(result);
    return result;
  }

  if (balanceFactor < -1 && value > node->right->data) {
    printCaseRotation("right", node);
    AVLNode *result = _rightCaseRotate(node);

    printResult(result);

    return result;
  }

  if (balanceFactor < -1 && value < node->right->data) {
    printCaseRotation("right left", node);
    AVLNode *result = _rightLeftCaseRotate(node);

    printResult(result);
    return result;
  }

  return node;
}

AVLNode *_findMinNode(AVLNode *node) {
  AVLNode *currNode = node;
  while (currNode && currNode->left != NULL)
    currNode = currNode->left;
  return currNode;
}

AVLNode *_remove_AVL(AVLNode *node, int value) {
  if (node == NULL)
    return node;
  if (value > node->data)
    node->right = _remove_AVL(node->right, value);
  else if (value < node->data)
    node->left = _remove_AVL(node->left, value);
  else {
    AVLNode *temp;
    if ((node->left == NULL) || (node->right == NULL)) {
      temp = NULL;
      if (node->left == NULL)
        temp = node->right;
      else if (node->right == NULL)
        temp = node->left;

      if (temp == NULL) {
        temp = node;
        node = NULL;
      } else
        *node = *temp;

      free(temp);
    } else {
      temp = _findMinNode(node->right);
      node->data = temp->data;
      node->right = _remove_AVL(node->right, temp->data);
    }
  }

  if (node == NULL)
    return node;

  node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1;

  int balanceFactor = _getBalanceFactor(node);

  if (balanceFactor > 1 && _getBalanceFactor(node->left) >= 0)
    return _leftCaseRotate(node);

  if (balanceFactor > 1 && _getBalanceFactor(node->left) < 0)
    return _leftRightCaseRotate(node);

  if (balanceFactor < -1 && _getBalanceFactor(node->right) <= 0)
    return _rightCaseRotate(node);

  if (balanceFactor < -1 && _getBalanceFactor(node->right) > 0)
    return _rightLeftCaseRotate(node);

  return node;
}

void avl_init(AVL *avl) {
  avl->_root = NULL;
  avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) { return avl->_root == NULL; }

bool avl_find(AVL *avl, int value) {
  AVLNode *temp = _search(avl->_root, value);
  if (temp == NULL)
    return false;

  if (temp->data == value)
    return true;
  else
    return false;
}

void avl_insert(AVL *avl, int value) {
  if (!avl_find(avl, value)) {
    avl->_root = _insert_AVL(avl, avl->_root, value);
    avl->_size++;
  }
}

void avl_remove(AVL *avl, int value) {
  if (avl_find(avl, value)) {
    avl->_root = _remove_AVL(avl->_root, value);
    avl->_size--;
  }
}

void freeTree(AVLNode *node) {
  if (node == NULL)
    return;

  freeTree(node->right);
  freeTree(node->left);

  free(node);
}

int main() {
  AVL avl = {0}, *p_avl = &avl;
  avl_init(p_avl);

  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    int a;
    scanf("%d", &a);

    avl_insert(p_avl, a);
  }

  /* postorder(avlku._root); */
  /* printf("\n"); */
  /* inorder(avlku._root); */
  /* printf("\n"); */
  /* preorder(avlku._root); */

  freeTree(p_avl->_root);
}
