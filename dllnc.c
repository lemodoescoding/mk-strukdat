#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
};

typedef struct Node TNode;

TNode *head;
TNode *tail;

bool isEmpty() { return (head == NULL) ? true : false; }

void insertAtBegin(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->prev = NULL;

  if (isEmpty()) {
    head = temp;
    tail = temp;
    head->next = NULL;
    head->prev = NULL;
  } else {
    temp->next = head;
    head->prev = temp;
    head = temp;
  }
}

void insertAtEnd(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->next = NULL;

  if (isEmpty()) {
    head = temp;
    head->next = NULL;
    head->prev = NULL;
  } else {
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
  }
}

void deleteAtBegin() {
  if (isEmpty())
    return;

  if (head == tail) {
    free(head);
    head = tail = NULL;
    return;
  }

  TNode *temp = head;

  temp->next->prev = NULL;
  head = temp->next;

  free(temp);

  temp = NULL;
}

void deleteAtEnd() {
  if (isEmpty())
    return;

  if (head == tail) {
    free(head);
    head = tail = NULL;
    return;
  }

  TNode *temp = tail;
  temp->prev->next = NULL;
  tail = temp->prev;

  free(temp);

  temp = NULL;
}

void freeLL() {
  if (isEmpty())
    return;

  TNode *temp = head;
  while (temp != NULL) {
    TNode *now = temp;

    temp = temp->next;

    free(now);
  }

  head = NULL;
  tail = NULL;
}

void printLL() {
  if (isEmpty())
    return;

  TNode *temp = head;
  while (temp != NULL) {
    printf("%d\n", temp->data);

    temp = temp->next;
  }

  temp = NULL;
}

int main() {
  insertAtBegin(1);
  insertAtBegin(3);
  insertAtBegin(5);
  insertAtBegin(7);
  insertAtBegin(8);
  deleteAtBegin();
  insertAtBegin(4);
  insertAtEnd(100);
  insertAtEnd(200);
  deleteAtEnd();
  insertAtEnd(300);
  insertAtEnd(400);

  printLL();
  freeLL();
  return 0;
}
