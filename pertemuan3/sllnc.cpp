#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
  int data;
  TNode *next;
} Node;

Node *head = NULL;
Node *tail = NULL;

bool isEmpty() { return (head == NULL) ? true : false; }

void insertAtBegin(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->next = NULL;

  if (isEmpty() == true) {
    head = temp;
    tail = temp;
    tail->next = NULL;
  } else {
    temp->next = head;
    head = temp;
  }
}

void insertAtEnd(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->next = NULL;

  if (isEmpty() == true) {
    head = temp;
    tail = temp;
    tail->next = NULL;
  } else {
    tail->next = temp;
    tail = temp;
  }
}

void printLL() {
  TNode *temp = head;
  while (temp->next != NULL) {
    printf("%d\n", temp->data);
    temp = temp->next;
  }

  printf("%d\n", temp->data);
}

void freeLL() {
  TNode *temp = head;
  while (temp->next != NULL) {

    TNode *now = temp;
    temp = temp->next;

    free(now);
  }

  head = NULL;
  tail = NULL;
}

int main() {
  insertAtBegin(2);
  insertAtBegin(3);
  insertAtBegin(5);
  insertAtBegin(7);
  insertAtBegin(11);
  insertAtEnd(13);
  insertAtEnd(17);

  printLL();
  freeLL();
  return 0;
}
