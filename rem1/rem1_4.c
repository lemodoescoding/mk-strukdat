#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char _character;
  struct Node *_next, *_prev;
} Node;

typedef struct {
  Node *_head, *_tail;
  size_t _size;
} Dequeue;

bool isDequeueEmpty(Dequeue *dq) {
  return (dq->_head == NULL && dq->_tail == NULL);
}

void DequeuePushBack(Dequeue *dq, char character) {
  Node *temp = (Node *)malloc(sizeof(Node));

  if (!temp)
    return;

  temp->_character = character;
  temp->_next = temp->_prev = NULL;

  dq->_size++;

  if (isDequeueEmpty(dq)) {
    dq->_head = dq->_tail = temp;
  } else {
    dq->_tail->_next = temp;
    temp->_prev = dq->_tail;
    dq->_tail = temp;
  }
}

void DequeuePopBack(Dequeue *dq) {
  if (isDequeueEmpty(dq))
    return;

  Node *dqback = dq->_tail;
  if (dq->_head == dq->_tail) {
    dq->_head = dq->_tail = NULL;
  } else {
    dq->_tail = dqback->_prev;
    dq->_tail->_next = NULL;
  }

  dq->_size--;
  free(dqback);
}

char DequeueFront(Dequeue *dq) {
  if (isDequeueEmpty(dq))
    return -1;

  return dq->_head->_character;
}

void traverseQueue(Node *temp) {
  if (temp == NULL)
    return;

  printf("%c", temp->_character);
  traverseQueue(temp->_next);
}

void processCommand(Dequeue *dq, char cmd[], char arg) {
  if (strcmp(cmd, "WRITE") == 0) {
    DequeuePushBack(dq, arg);
  } else if (strcmp(cmd, "BACKSPACE") == 0) {
    DequeuePopBack(dq);
  } else if (strcmp(cmd, "PRINT") == 0) {
    traverseQueue(dq->_head);
  }
}

int main() {
  Dequeue dq = {0}, *p_dq = &dq;

  char command[20], arg = 0;
  while (true) {
    scanf("%s", command);

    if (strcmp(command, "WRITE") == 0)
      scanf(" %c", &arg);

    processCommand(p_dq, command, arg);

    if (strcmp(command, "PRINT") == 0) {
      break;
    }
  }

  return 0;
}
