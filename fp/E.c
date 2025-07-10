#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NEG_INT -32767

typedef struct Node {
  int _data;
  struct Node *_next, *_prev;
} QNode;

typedef struct {
  QNode *_head, *_tail;
  size_t _size;
} Dequeue;

bool isEmptyDequeue(Dequeue *d) {
  return (d->_head == NULL && d->_tail == NULL);
}

void DQPushBack(Dequeue *d, int nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  temp->_data = nd;
  temp->_next = temp->_prev = NULL;

  d->_size++;

  if (isEmptyDequeue(d)) {
    d->_head = d->_tail = temp;
  } else {
    d->_tail->_next = temp;
    temp->_prev = d->_tail;
    d->_tail = temp;
  }
}

void DQPushFront(Dequeue *d, int nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  temp->_data = nd;
  temp->_prev = temp->_next = NULL;

  d->_size++;

  if (isEmptyDequeue(d)) {
    d->_head = d->_tail = temp;
  } else {
    temp->_next = d->_head;
    d->_head->_prev = temp;
    d->_head = temp;
  }
}

void DQPopBack(Dequeue *d) {
  if (isEmptyDequeue(d))
    return;

  QNode *temp = d->_tail;
  if (d->_head == d->_tail) {
    d->_head = d->_tail = NULL;
  } else {
    d->_tail = temp->_prev;
    d->_tail->_next = NULL;
  }

  free(temp);
  d->_size--;
}

void DQPopFront(Dequeue *d) {
  if (isEmptyDequeue(d))
    return;

  QNode *temp = d->_head;
  if (d->_head == d->_tail) {
    d->_head = d->_tail = NULL;
  } else {
    d->_head = temp->_next;
    d->_head->_prev = NULL;
  }

  free(temp);
  d->_size--;
}

int DQFront(Dequeue *d) {
  if (isEmptyDequeue(d))
    return NEG_INT;

  return d->_head->_data;
}

int DQBack(Dequeue *d) {
  if (isEmptyDequeue(d))
    return NEG_INT;

  return d->_tail->_data;
}

void DQReverseFrontBack(Dequeue *d) {
  if (d->_size < 2 || isEmptyDequeue(d))
    return;

  int head_temp = d->_head->_data;
  int tail_temp = d->_tail->_data;

  d->_head->_data = tail_temp;
  d->_tail->_data = head_temp;
}

int main() {
  int N;
  scanf("%d", &N);

  Dequeue q = {0}, *p_q = &q;
  p_q->_head = p_q->_tail = NULL;
  p_q->_size = 0;

  for (int i = 0; i < N; i++) {
    char cmd[100];

    int sec_arg = 0;

    scanf("%s", cmd);

    if (strcmp(cmd, "tambahDepan") == 0) {
      scanf(" %d", &sec_arg);
      DQPushFront(p_q, sec_arg);
    } else if (strcmp(cmd, "tambahBelakang") == 0) {
      scanf(" %d", &sec_arg);
      DQPushBack(p_q, sec_arg);
    } else if (strcmp(cmd, "depan") == 0) {
      int front = DQFront(p_q);

      if (front == NEG_INT)
        printf("\n");

      else {
        printf("%d\n", front);
        DQPopFront(p_q);
      }
    } else if (strcmp(cmd, "belakang") == 0) {
      int tail = DQBack(p_q);

      if (tail == NEG_INT)
        printf("\n");

      else {
        printf("%d\n", tail);
        DQPopBack(p_q);
      }
    } else if (strcmp(cmd, "balik") == 0) {
      DQReverseFrontBack(p_q);
    }
  }

  return 0;
}
