#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEG_INT -32767

typedef struct QNode {
  char _name[11];
  char _kritis[10];
  int _age;
  int _arrivalTime;
  struct QNode *_next;
} QNode;

typedef struct {
  QNode *_top;
  size_t _size;
} PriorityQueue;

bool isPQEmpty(PriorityQueue *pq) { return (pq->_top == NULL); }

int getKritisLevel(QNode *s) {
  if (strcmp(s->_kritis, "Ringan") == 0)
    return 0;
  if (strcmp(s->_kritis, "Sedang") == 0)
    return 1;
  return 2;
}

int comparePriority(QNode *pa, QNode *pb) {
  int kritisA = getKritisLevel(pa), kritisB = getKritisLevel(pb);

  if (kritisA != kritisB)
    return kritisA - kritisB;
  if (pa->_age != pb->_age)
    return pa->_age - pb->_age;
  if (pa->_arrivalTime != pb->_arrivalTime)
    return pa->_arrivalTime - pb->_arrivalTime;

  return strcmp(pa->_name, pb->_name);
}

void PQPush(PriorityQueue *pq, char name[], int age, int arrivalTime,
            char kritis[]) {
  QNode *temp = (QNode *)malloc(sizeof(QNode));

  if (!temp)
    return;

  strcpy(temp->_name, name);
  strcpy(temp->_kritis, kritis);
  temp->_age = age;
  temp->_arrivalTime = arrivalTime;
  temp->_next = NULL;

  pq->_size++;

  if (isPQEmpty(pq)) {
    pq->_top = temp;
  } else if (comparePriority(temp, pq->_top) < 0) {
    temp->_next = pq->_top;
    pq->_top = temp;
  } else {
    QNode *tempNode = pq->_top;

    while (tempNode->_next != NULL &&
           (comparePriority(temp, tempNode->_next) >= 0)) {
      tempNode = tempNode->_next;
    }

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

void PQTop(PriorityQueue *pq) {
  printf("Pasien atas nama %s dengan detik kedatangan %d berumur %d harap "
         "segera datang ke ruang penyakit %s\n",
         pq->_top->_name, pq->_top->_arrivalTime, pq->_top->_age,
         pq->_top->_kritis);
}

int main() {
  PriorityQueue pq = {0}, *p_pq = &pq;

  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    int K, U;
    char M[11], P[10];
    scanf("%d %s %d %s", &K, M, &U, P);

    PQPush(p_pq, M, U, K, P);
  }

  do {
    PQTop(p_pq);
    PQPop(p_pq);
  } while (--N > 0);
}
