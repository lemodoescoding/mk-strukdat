#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct Node TNode;

TNode *head;
TNode *tail;

bool isEmptyLL() { return (head == NULL) ? true : false; }

void insertAtBegin(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->next = NULL;

  if (isEmptyLL() == true) {
    head = temp;
    tail = temp;
    tail->next = temp;
  } else {
    temp->next = head;
    head = temp;
    tail->next = head;
  }
}

void insertAtEnd(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->next = NULL;

  if (isEmptyLL() == true) {
    head = temp;
    tail = temp;
    tail->next = temp;
  } else {
    tail->next = temp;
    tail = temp;
    temp->next = head;
  }
}

void deleteAtBegin() {
  if (isEmptyLL())
    return;

  if (head == tail) {
    free(head);
    head = tail = NULL;
    return;
  }

  TNode *temp = head;
  tail->next = head->next;

  head = head->next;

  free(temp);
}

void deleteAtEnd() {
  if (isEmptyLL())
    return;

  if (head == tail) {
    free(head);
    head = tail = NULL;
    return;
  }

  TNode *temp = head;
  while (temp->next != tail) {
    temp = temp->next;
  }

  temp->next = tail->next;
  free(tail);

  tail = temp;
}

void printLL() {
  if (isEmptyLL() == true)
    return;

  TNode *temp = head;
  while (temp->next != head) {
    printf("%d\n", temp->data);
    temp = temp->next;
  }

  printf("%d\n", temp->data);
  temp = NULL;
}

void freeLL() {
  if (isEmptyLL() == true)
    return;

  tail->next = NULL;

  TNode *temp = head;
  while (temp != NULL) {
    TNode *now = temp;

    temp = temp->next;

    free(now);
  }

  head = NULL;
  tail = NULL;
}

int main() {
  insertAtEnd(33);
  insertAtEnd(33);

  deleteAtEnd();

  printLL();
  freeLL();
  return 0;
}
