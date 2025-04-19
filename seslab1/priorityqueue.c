#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NEG_INT -32767

typedef struct QNode {
  int _data;
  struct QNode *_next;
} QNode;

typedef struct {
  QNode *_top;
  size_t _size;
} PriorityQueue;

bool isPQEmpty(PriorityQueue *pq) { return (pq->_top == NULL); }

void PQPush(PriorityQueue *pq, int nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  temp->_data = nd;
  temp->_next = NULL;

  pq->_size++;

  if (isPQEmpty(pq)) {
    pq->_top = temp;
  } else if (nd < pq->_top->_data) {
    temp->_next = pq->_top;
    pq->_top = temp;
  } else {
    QNode *tempNode = pq->_top;

    while (tempNode->_next != NULL && tempNode->_next->_data < nd)
      tempNode = tempNode->_next;

    temp->_next = tempNode->_next;
    tempNode->_next = temp;
  }
}

void PQPop(PriorityQueue *pq) {
  if (isPQEmpty(pq))
    return;

  QNode *temp = pq->_top;
  pq->_top = temp->_next;

  free(temp);
  pq->_size--;
}

int PQTop(PriorityQueue *pq) {
  return (!isPQEmpty(pq)) ? pq->_top->_data : NEG_INT;
}

int main() {
  PriorityQueue pq = {0}, *p_pq = &pq;

  PQPush(p_pq, 3);
  PQPush(p_pq, 5);
  PQPush(p_pq, 2);
  PQPush(p_pq, 1);

  printf("%d\n", PQTop(p_pq));

  PQPop(p_pq);

  printf("%d\n", PQTop(p_pq));

  return 0;
}
