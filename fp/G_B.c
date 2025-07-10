#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_HASH 101

typedef struct TreeNode {
  char name[MAX_NAME];
  struct TreeNode *parent;
  struct TreeNode **children;
  int child_count;
} TreeNode;

typedef struct NodeMap {
  char key[MAX_NAME];
  TreeNode *node;
  struct NodeMap *next;
} NodeMap;

typedef struct TreeMap {
  NodeMap *table[MAX_HASH];
} TreeMap;

unsigned int hash(const char *str) {
  unsigned int h = 5381;
  int c;
  while ((c = *str++))
    h = ((h << 5) + h) + c;
  return h % MAX_HASH;
}

void map_init(TreeMap *map) {
  for (int i = 0; i < MAX_HASH; i++)
    map->table[i] = NULL;
}

TreeNode *map_get(TreeMap *map, const char *key) {
  unsigned int idx = hash(key);
  NodeMap *entry = map->table[idx];
  while (entry) {
    if (strcmp(entry->key, key) == 0)
      return entry->node;
    entry = entry->next;
  }
  return NULL;
}

void map_put(TreeMap *map, const char *key, TreeNode *node) {
  unsigned int idx = hash(key);
  NodeMap *entry = map->table[idx];
  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      entry->node = node;
      return;
    }
    entry = entry->next;
  }
  NodeMap *newEntry = malloc(sizeof(NodeMap));
  strcpy(newEntry->key, key);
  newEntry->node = node;
  newEntry->next = map->table[idx];
  map->table[idx] = newEntry;
}

TreeNode *create_node(const char *name) {
  TreeNode *node = malloc(sizeof(TreeNode));
  strcpy(node->name, name);
  node->parent = NULL;
  node->children = NULL;
  node->child_count = 0;
  return node;
}

void add_child(TreeNode *parent, TreeNode *child) {
  parent->children =
      realloc(parent->children, sizeof(TreeNode *) * (parent->child_count + 1));
  parent->children[parent->child_count++] = child;
  child->parent = parent;
}

void read_tree(TreeMap *map) {
  char parent[MAX_NAME], child[MAX_NAME];
  while (1) {
    scanf("%s", parent);
    if (strcmp(parent, "0") == 0)
      break;
    scanf("%s", child);

    TreeNode *parentNode = map_get(map, parent);
    if (!parentNode) {
      parentNode = create_node(parent);
      map_put(map, parent, parentNode);
    }

    TreeNode *childNode = map_get(map, child);
    if (!childNode) {
      childNode = create_node(child);
      map_put(map, child, childNode);
    }

    add_child(parentNode, childNode);
  }
}

void compare_trees(TreeMap *oldMap, TreeMap *newMap) {
  int updates = 0, insertions = 0, deletions = 0;

  // Check for deletions and updates
  for (int i = 0; i < MAX_HASH; i++) {
    NodeMap *entry = oldMap->table[i];
    while (entry) {
      TreeNode *oldNode = entry->node;
      TreeNode *newNode = map_get(newMap, oldNode->name);
      if (!newNode) {
        deletions++;
      } else {
        const char *oldParent = oldNode->parent ? oldNode->parent->name : "";
        const char *newParent = newNode->parent ? newNode->parent->name : "";
        if (strcmp(oldParent, newParent) != 0) {
          updates++;
        }
      }
      entry = entry->next;
    }
  }

  // Check for insertions
  for (int i = 0; i < MAX_HASH; i++) {
    NodeMap *entry = newMap->table[i];
    while (entry) {
      TreeNode *newNode = entry->node;
      TreeNode *oldNode = map_get(oldMap, newNode->name);
      if (!oldNode) {
        insertions++;
      }
      entry = entry->next;
    }
  }

  printf("%d update%s, +%d insertion%s, -%d deletion%s\n", updates,
         updates == 1 ? "" : "s", insertions, insertions == 1 ? "" : "s",
         deletions, deletions == 1 ? "" : "s");
}

void free_tree(TreeNode *node) {
  for (int i = 0; i < node->child_count; i++)
    free_tree(node->children[i]);
  free(node->children);
  free(node);
}

void free_map(TreeMap *map) {
  for (int i = 0; i < MAX_HASH; i++) {
    NodeMap *entry = map->table[i];
    while (entry) {
      NodeMap *temp = entry;
      entry = entry->next;
      free(temp);
    }
  }
}

int main() {
  TreeMap oldMap, newMap;
  map_init(&oldMap);
  map_init(&newMap);

  read_tree(&oldMap);
  read_tree(&newMap);

  compare_trees(&oldMap, &newMap);

  // Optional: Free nodes from maps
  // Nodes themselves are unique, so free each node once
  for (int i = 0; i < MAX_HASH; i++) {
    NodeMap *entry = oldMap.table[i];
    while (entry) {
      free_tree(entry->node);
      entry = entry->next;
    }
  }

  free_map(&oldMap);
  free_map(&newMap);
  return 0;
}
