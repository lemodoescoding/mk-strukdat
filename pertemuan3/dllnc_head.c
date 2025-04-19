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

bool isEmpty() { return (head == NULL) ? true : false; }

void insertAtBegin(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;
  temp->prev = NULL;

  if (isEmpty()) {
    head = temp;
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

    TNode *help = head;
    while (help->next != NULL) {
      help = help->next;
    }

    help->next = temp;
    temp->prev = help;
  }
}

void deleteAtBegin() {
  if (isEmpty())
    return;

  if (head->next == NULL && head->prev == NULL) {
    free(head);
    head = NULL;
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

  if (head->next == NULL && head->prev == NULL) {
    free(head);
    head = NULL;
    return;
  }

  TNode *temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->prev->next = NULL;

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
  deleteAtBegin();

  printLL();
  freeLL();
  return 0;
}
