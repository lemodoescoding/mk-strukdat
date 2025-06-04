#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 20

typedef struct HashNode {
  int key, value;
} HashNode;

struct HashNode **arr;
struct HashNode *dummy;

int size = 0;

void insert(int K, int V) {
  HashNode *temp = (HashNode *)malloc(sizeof(HashNode));

  temp->key = K;
  temp->value = V;

  int hashIndex = (K % CAPACITY);

  while (arr[hashIndex] != NULL && arr[hashIndex]->key != K &&
         arr[hashIndex]->key != -1) {
    hashIndex++;
    hashIndex %= CAPACITY;
  }

  if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
    size++;

  arr[hashIndex] = temp;
}

int delete(int K) {
  int hashIndex = (K % CAPACITY);

  while (arr[hashIndex] != NULL) {
    if (arr[hashIndex]->key == K) {
      arr[hashIndex] = dummy;

      size--;

      return 1;
    }

    hashIndex++;
    hashIndex %= CAPACITY;
  }

  return 0;
}

int find(int K) {
  int hashIndex = K % CAPACITY;

  int counter = 0;

  while (arr[hashIndex] != NULL) {
    if (counter++ > CAPACITY)
      break;

    if (arr[hashIndex]->key == K)
      return arr[hashIndex]->value;

    hashIndex++;
    hashIndex %= CAPACITY;
  }

  return -1;
}

int main() {
  arr = (HashNode **)malloc(sizeof(HashNode *) * CAPACITY);

  for (int i = 0; i < CAPACITY; i++)
    arr[i] = NULL;

  dummy = (HashNode *)malloc(sizeof(HashNode));

  dummy->key = -1;
  dummy->value = -1;

  insert(1, 5);
  insert(2, 15);
  insert(3, 20);
  insert(4, 7);

  if (find(4) != -1)
    printf("Value of Key 5 = %d\n", find(4));
  else
    printf("Key 4 does not exists\n");

  if (delete(4))
    printf("Node value of key 4 is deleted "
           "successfully\n");
  else {
    printf("Key does not exists\n");
  }

  if (find(4) != -1)
    printf("Value of Key 4 = %d\n", find(4));
  else
    printf("Key 4 does not exists\n");
}
