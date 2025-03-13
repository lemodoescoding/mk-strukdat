#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

bool isEmpty() { return (head == NULL) ? true : false; }

void insertAtBegin(int nd) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
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
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
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

void deleteAtBegin() {
  if (isEmpty())
    return;
  if (head == tail) {
    free(head);
    head = tail = NULL;
    return;
  }

  struct Node *temp = head;
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

  struct Node *temp = head;
  while (temp->next != tail) {
    temp = temp->next;
  }

  tail = temp;
  free(temp->next);
  temp->next = NULL;
}

void printLL() {
  if (isEmpty())
    return;
  struct Node *temp = head;
  while (temp != NULL) {
    printf("%d\n", temp->data);
    temp = temp->next;
  }
}

void freeLL() {
  if (isEmpty())
    return;

  struct Node *temp = head;
  while (temp != NULL) {

    struct Node *now = temp;
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

  deleteAtEnd();

  printLL();
  freeLL();
  return 0;
}
