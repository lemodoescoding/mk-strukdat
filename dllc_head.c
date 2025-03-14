#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
};

typedef struct Node TNode;

TNode *head = NULL;

bool isEmpty() { return (head == NULL) ? true : false; }

void insertAtBegin(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;

  if (isEmpty()) {
    head = temp;
    head->next = temp;
    head->prev = temp;
  } else {
    TNode *help = head->prev;
    temp->next = head;
    head->prev = temp;
    head = temp;
    head->prev = help;
    help->next = head;
  }
}

void insertAtEnd(int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  temp->data = nd;

  if (isEmpty()) {
    head = temp;
    head->next = temp;
    head->prev = temp;
  } else {
    TNode *help = head;
    while (help->next != head) {
      help = help->next;
    }

    help->next = temp;
    temp->prev = help;
    head->prev = temp;
    temp->next = head;
  }
}

void printLL() {
  if (isEmpty())
    return;

  TNode *temp = head;
  do {
    printf("%d\n", temp->data);
    temp = temp->next;

  } while (temp != head);
}

void freeLL() {
  if (isEmpty())
    return;
  TNode *temp = head->next;

  do {
    TNode *now = temp;
    temp = temp->next;

    free(now);
  } while (temp != head);

  free(head);

  head = NULL;
}

int main() {
  insertAtEnd(1);
  insertAtBegin(5);
  insertAtBegin(4);
  insertAtEnd(2);
  insertAtBegin(3);

  printLL();
  freeLL();
  return 0;
}
