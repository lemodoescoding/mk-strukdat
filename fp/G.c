#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 101
#define MAX_CHILD 100

typedef struct TreeNode {
  char name[MAX_NAME];
  struct TreeNode *parent;
  struct TreeNode *children[MAX_CHILD];
  int children_count;
} TreeNode;

typedef struct FolderTree {
  struct TreeNode *root;
} FolderTree;

typedef struct NodeList {
  TreeNode **nodes;
  size_t size, max;
} NodeList;

TreeNode *findNode(NodeList *list, const char *name) {
  for (int i = 0; i < list->size; i++) {
    if (strcmp(list->nodes[i]->name, name) == 0)
      return list->nodes[i];
  }

  return NULL;
}

bool existNode(NodeList *list, const char *name) {
  return findNode(list, name) != NULL;
}

TreeNode *createNode(const char *name) {
  TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
  strcpy(temp->name, name);
  temp->parent = NULL;
  temp->children_count = 0;

  return temp;
}
void addChild(TreeNode *parent, TreeNode *child) {
  parent->children[parent->children_count++] = child;
  child->parent = parent;
};

void readInputUser(NodeList *list, FolderTree *root) {
  char parentName[MAX_NAME], childName[MAX_NAME];

  list->nodes = malloc(sizeof(TreeNode *) * 16);
  list->size = 0;
  list->max = 16;

  while (1) {
    scanf("%s", parentName);
    scanf(" %s", childName);

    if (strcmp(parentName, "0") == 0 && strcmp(childName, "0") == 0) {
      break;
    }

    TreeNode *parent = findNode(list, parentName);
    if (!parent) {
      parent = createNode(parentName);

      if (list->size + 1 >= list->max) {
        list->max *= 2;
        list->nodes = realloc(list->nodes, sizeof(TreeNode *) * list->max);
      }

      list->nodes[list->size++] = parent;
    }

    TreeNode *child = findNode(list, childName);
    if (!child) {
      child = createNode(parentName);

      if (list->size + 1 >= list->max) {
        list->max *= 2;
        list->nodes = realloc(list->nodes, sizeof(TreeNode *) * list->max);
      }

      list->nodes[list->size++] = child;
    }

    addChild(parent, child);

    if (strcmp(parentName, "root") == 0) {
      root->root = parent;
    }
  }
}

void compareTwoTree(FolderTree *oldTree, FolderTree *newTree) {}
void freeTree(TreeNode *tree) {}

int main() { return 0; }
