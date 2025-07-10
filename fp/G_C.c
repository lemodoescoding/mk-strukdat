#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 101
#define MAX_NODES 100

typedef struct TreeNode {
  char name[MAX_NAME];
  int child_count;
  struct TreeNode *parent;
  struct TreeNode *children[MAX_NODES];
} TreeNode;

typedef struct {
  TreeNode *nodes[MAX_NODES];
  size_t size;
} NodeList;

TreeNode *findNode(NodeList *list, const char *name) {
  for (int i = 0; i < list->size; i++) {
    if (strcmp(list->nodes[i]->name, name) == 0)
      return list->nodes[i];
  }

  return NULL;
}

TreeNode *createNode(const char *name) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  strcpy(node->name, name);
  node->parent = NULL;
  node->child_count = 0;

  return node;
}

void add_child(TreeNode *parent, TreeNode *child) {
  parent->children[parent->child_count++] = child;
  child->parent = parent;
}

void readTree(NodeList *list, TreeNode **root) {
  char parentName[MAX_NAME], childName[MAX_NAME];
  while (1) {
    scanf("%s", parentName);

    scanf(" %s", childName);

    if (strcmp(parentName, "0") == 0 && strcmp(childName, "0") == 0)
      break;

    TreeNode *parent = findNode(list, parentName);
    if (!parent) {
      parent = createNode(parentName);
      list->nodes[list->size++] = parent;
    }

    TreeNode *child = findNode(list, childName);
    if (!child) {
      child = createNode(childName);
      list->nodes[list->size++] = child;
    }

    add_child(parent, child);
  }

  for (int i = 0; i < list->size; i++) {
    if (strcmp(list->nodes[i]->name, "root") == 0) {
      *root = list->nodes[i];
      break;
    }
  }
}

void compare_trees(NodeList *old_list, NodeList *new_list) {
  int updates = 0, insertions = 0, deletions = 0;

  for (int i = 0; i < old_list->size; i++) {
    TreeNode *old_node = old_list->nodes[i];
    TreeNode *new_node = findNode(new_list, old_node->name);

    if (!new_node) {
      deletions++;
      continue;
    }
  }

  printf("%d update%s, +%d insertion%s, -%d deletion%s\n", updates,
         updates == 1 ? "" : "s", insertions, insertions == 1 ? "" : "s",
         deletions, deletions == 1 ? "" : "s");
}

void free_tree(TreeNode *node) {
  for (int i = 0; i < node->child_count; i++) {
    free_tree(node->children[i]);
  }
  free(node);
}

int main() {
  NodeList old_list = {.size = 0}, new_list = {.size = 0};
  TreeNode *old_root = NULL, *new_root = NULL;

  readTree(&old_list, &old_root);
  readTree(&new_list, &new_root);

  compare_trees(&old_list, &new_list);

  for (int i = 0; i < old_list.size; i++) {
    free_tree(old_list.nodes[i]);
  }

  for (int i = 0; i < new_list.size; i++) {
    free_tree(new_list.nodes[i]);
  }

  return 0;
}
