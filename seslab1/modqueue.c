#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int _data;
  struct Node *_next;
  struct Node *_prev;
} QNode;

typedef struct {
  QNode *_front;
  QNode *_rear;
  size_t _size;
} ModQueue;

typedef struct {
  QNode *_head;
  QNode *_tail;
  size_t _size;
} ModDequeue;

bool isEmptyDeqeue(ModDequeue *d) {
  return (d->_head == NULL && d->_tail == NULL);
}

bool isEmptyQueue(ModQueue *q) {
  return (q->_front == NULL && q->_rear == NULL);
}

void QPush(ModQueue *q, int nd) {
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

void QPop(ModQueue *q) {
  if (isEmptyQueue(q))
    return;

  QNode *temp = q->_front;

  if (q->_front == q->_rear) {
    q->_front = q->_rear = NULL;
  } else {
    q->_front = temp->_next;
  }

  q->_size--;
  free(temp);
}

int QFront(ModQueue *q) {
  if (isEmptyQueue(q))
    return -32767;

  return q->_front->_data;
}

int QBack(ModQueue *q) {
  if (isEmptyQueue(q))
    return -32767;

  return q->_rear->_data;
}

void DQPushFront(ModDequeue *d, int nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  d->_size++;

  temp->_data = nd;
  temp->_next = temp->_prev = NULL;

  if (isEmptyDeqeue(d)) {
    d->_head = d->_tail = temp;
  } else {
    temp->_next = d->_head;
    d->_head->_prev = temp;
    d->_head = temp;
  }
}

void DQPushBack(ModDequeue *d, int nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  d->_size++;
  temp->_data = nd;
  temp->_next = temp->_prev = NULL;

  if (isEmptyDeqeue(d)) {
    d->_head = d->_tail = temp;
  } else {
    d->_tail->_next = temp;
    temp->_prev = d->_tail;
    d->_tail = temp;
  }
}

int DQFront(ModDequeue *d) {
  if (isEmptyDeqeue(d))
    return -32767;

  return d->_head->_data;
}

int DQBack(ModDequeue *d) {
  if (isEmptyDeqeue(d))
    return -32767;

  return d->_tail->_data;
}

void DQPopFront(ModDequeue *d) {
  if (isEmptyDeqeue(d))
    return;

  QNode *temp = d->_head;

  if (d->_head == d->_tail) {
    d->_head = d->_tail = NULL;
  } else {
    d->_head = temp->_next;
    d->_head->_prev = NULL;
  }

  d->_size--;
  free(temp);
}

void DQPopBack(ModDequeue *d) {
  if (isEmptyDeqeue(d))
    return;

  QNode *temp = d->_tail;

  if (d->_head == d->_tail) {
    d->_head = d->_tail = NULL;
  } else {
    d->_tail = temp->_prev;
    d->_tail->_next = NULL;
  }

  d->_size--;
  free(temp);
}

void EnqueueModDQQ(ModQueue *q, ModDequeue *d, int nd) {
  if (isEmptyQueue(q)) {
    QPush(q, nd);
    DQPushBack(d, nd);
  } else {

    QPush(q, nd);

    while (!isEmptyDeqeue(d) && DQBack(d) > nd) {
      DQPopBack(d);
    }

    DQPushBack(d, nd);
  }
}

void DequeueModDQQ(ModQueue *q, ModDequeue *d) {
  if (QFront(q) == DQFront(d)) {
    QPop(q);
    DQPopFront(d);
  } else {
    QPop(q);
  }
}

int GetMinModDQQ(ModDequeue *d) { return DQFront(d); }

int main(void) {
  ModQueue q = {0};
  ModDequeue d = {0};

  int example[4] = {1, 2, 4, 3};

  for (int i = 0; i < 4; i++) {
    EnqueueModDQQ(&q, &d, example[i]);
  }

  printf("Smallest: %d\n", GetMinModDQQ(&d));

  EnqueueModDQQ(&q, &d, 6);
  DequeueModDQQ(&q, &d);

  printf("Smallest: %d\n", GetMinModDQQ(&d));

  EnqueueModDQQ(&q, &d, 5);
  DequeueModDQQ(&q, &d);

  printf("Smallest: %d\n", GetMinModDQQ(&d));

  EnqueueModDQQ(&q, &d, 1);
  DequeueModDQQ(&q, &d);

  printf("Smallest: %d\n", GetMinModDQQ(&d));
}
