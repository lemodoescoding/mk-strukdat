#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

typedef struct QNode {
  ll _data;
  struct QNode *_next;
} QNode;

typedef struct {
  QNode *_top;
  size_t _size;
} PriorityQueue;

bool isPQEmpty(PriorityQueue *pq) { return (pq->_top == NULL); }

void PQPush(PriorityQueue *pq, ll nd) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  temp->_data = nd;
  temp->_next = NULL;

  pq->_size++;

  if (isPQEmpty(pq)) {
    pq->_top = temp;
  } else if (nd > pq->_top->_data) {
    temp->_next = pq->_top;
    pq->_top = temp;
  } else {
    QNode *tempNode = pq->_top;

    while (tempNode->_next != NULL && tempNode->_next->_data > nd)
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

ll PQTop(PriorityQueue *pq) { return (!isPQEmpty(pq)) ? pq->_top->_data : 0; }
char convertWeight(char w) {
  switch (w) {
  case '!':
    return '1';
  case '@':
    return '2';
  case '#':
    return '3';
  case '$':
    return '4';
  case '%':
    return '5';
  case '^':
    return '6';
  case '&':
    return '7';
  case '*':
    return '8';
  case '(':
    return '9';
  case ')':
    return '0';
  }
}

ll convertFishDayTW(char fish[], int length) {
  char converted[length];
  for (int i = 0; i < length; i++) {
    converted[i] = convertWeight(fish[i]);
  }

  return atol(converted);
}

int main() {
  int n;
  ll M;

  scanf("%d %lld", &n, &M);
  scanf("\n");

  PriorityQueue pq = {0}, *p_pq = &pq;

  ll fishes[n];

  for (int i = 0; i < n; i++) {
    char fish[6];

    scanf("%s", fish);

    fishes[i] = convertFishDayTW(fish, strlen(fish));
  }

  for (int i = 0; i < n; i++) {
    if (fishes[i] != M) {
      PQPush(p_pq, fishes[i]);
    } else {
      printf("%lld", fishes[i]);
      --M;

      if (PQTop(p_pq) == M) {
        printf(" ");
      }
    }

    if (PQTop(p_pq) < M) {
      printf("\n");
      continue;
    }

    while (PQTop(p_pq) == M && !isPQEmpty(p_pq)) {
      printf("%lld", PQTop(p_pq));

      --M;

      PQPop(p_pq);

      if (PQTop(p_pq) == M) {
        printf(" ");
      }
    }

    printf("\n");
  }
}
