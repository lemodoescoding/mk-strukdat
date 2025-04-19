#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ll long long

typedef struct Node {
  ll _weight;
  struct Node *_next;
} Node;

typedef struct {
  Node *_top;
  size_t _size;
} PriorityQueue;

bool isPQEmpty(PriorityQueue *pq) { return (pq->_top == NULL); }

void PQPush(PriorityQueue *pq, ll weight) {
  Node *temp = (Node *)malloc(sizeof(Node));

  if (!temp)
    return;

  temp->_weight = weight;
  temp->_next = NULL;

  pq->_size++;

  if (isPQEmpty(pq)) {
    pq->_top = temp;
  } else if (weight >= pq->_top->_weight) {
    temp->_next = pq->_top;
    pq->_top = temp;
  } else {
    Node *tempNode = pq->_top;

    while (tempNode->_next != NULL && tempNode->_next->_weight > weight)
      tempNode = tempNode->_next;

    temp->_next = tempNode->_next;
    tempNode->_next = temp;
  }
}

void PQPop(PriorityQueue *pq) {
  if (isPQEmpty(pq))
    return;

  Node *temp = pq->_top;
  pq->_top = temp->_next;

  free(temp);
  pq->_size--;
}

ll PQTop(PriorityQueue *pq) {
  if (isPQEmpty(pq))
    return -1;

  return pq->_top->_weight;
}

int main() {
  PriorityQueue pq = {0}, *p_pq = &pq;

  int N;
  scanf("%d", &N);

  ll weight = 0;
  for (int i = 0; i < N; i++) {
    scanf("%lld", &weight);
    PQPush(p_pq, weight);
  }

  while (true) {

    if (p_pq->_size == 0 || p_pq->_size == 1)
      break;
    ll R, T;

    Node *topnow = p_pq->_top;
    Node *nextNode = topnow->_next;

    T = topnow->_weight;
    R = nextNode->_weight;

    PQPop(p_pq);
    PQPop(p_pq);

    if (R == T) {
      continue;
    } else if (R < T) {
      int diff = T - R;
      PQPush(p_pq, diff);
    }
  }

  if (p_pq->_size == 1) {
    printf("%lld", PQTop(p_pq));
  }

  if (p_pq->_size == 0)
    printf("0");
}
