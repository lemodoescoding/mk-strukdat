#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NEG_INT -32767

typedef struct Node {
  int _data;
  struct Node *_next, *_prev;
} QNode;

typedef struct {
  QNode *_front, *_rear;
  size_t _size;
} Queue;

typedef struct {
  QNode *_head, *_tail;
  size_t _size;
} Dequeue;

bool isEmptyQueue(Queue *q) { return (q->_front == NULL && q->_rear == NULL); }
bool isEmptyDequeue(Dequeue *d) {
  return (d->_head == NULL && d->_tail == NULL);
}

void QPush(Queue *q, int nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  q->_size++;
  temp->_data = nd;
  temp->_next = temp->_prev = NULL;

  if (isEmptyQueue(q)) {
    q->_front = q->_rear = temp;
  } else {
    q->_rear->_next = temp;
    q->_rear = temp;
  }
}

void QPop(Queue *q) {
  if (isEmptyQueue(q))
    return;

  QNode *temp = q->_front;

  if (q->_front == q->_rear) {
    q->_front = q->_rear = NULL;
  } else {
    q->_front = temp->_next;
  }

  free(temp);
  q->_size--;
}

int QBack(Queue *q) {
  if (isEmptyQueue(q))
    return NEG_INT;

  return q->_rear->_data;
}

int QFront(Queue *q) {
  if (isEmptyQueue(q))
    return NEG_INT;

  return q->_front->_data;
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

void EnqueueModDQQ(Queue *q, Dequeue *d, int nd) {
  if (isEmptyQueue(q)) {
    QPush(q, nd);
    DQPushBack(d, nd);
  } else {
    QPush(q, nd);

    while (!isEmptyDequeue(d) && DQBack(d) > nd) {
      DQPopBack(d);
    }

    DQPushBack(d, nd);
  }
}

void DequeueModDQQ(Queue *q, Dequeue *d) {
  if (QFront(q) == DQFront(d)) {
    QPop(q);
    DQPopFront(d);
  } else {
    QPop(q);
  }
}

int GetMinModDQQ(Dequeue *d) { return DQFront(d); }

int main() {
  Queue q = {0}, *p_q = &q;
  Dequeue d = {0}, *p_d = &d;

  int N = 0, M = 0;
  scanf("%d %d", &N, &M);

  int A[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }

  int j = 0;
  for (; j < M; j++) {
    EnqueueModDQQ(p_q, p_d, A[j]);
  }

  int check_time = N - M + 1;
  do {
    printf("%d\n", GetMinModDQQ(p_d));
    DequeueModDQQ(p_q, p_d);
    EnqueueModDQQ(p_q, p_d, A[j++]);
  } while (--check_time > 0);
}
