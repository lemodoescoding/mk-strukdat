#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int _transaksi;
  struct Node *_next;
} Node;

typedef struct {
  Node *_head, *_tail;
  size_t _size;
} Queue;

bool isQueueEmpty(Queue *q) { return (q->_head == NULL); }

void QueuePush(Queue *q, int transaksi) {
  Node *temp = (Node *)malloc(sizeof(Node));

  if (!temp)
    return;

  q->_size++;
  temp->_transaksi = transaksi;
  temp->_next = NULL;

  if (isQueueEmpty(q)) {
    q->_head = q->_tail = temp;
  } else {
    q->_tail->_next = temp;
    q->_tail = temp;
  }
}

void QueuePop(Queue *q) {
  if (isQueueEmpty(q))
    return;

  Node *top_temp = q->_head;
  q->_head = top_temp->_next;

  free(top_temp);
  q->_size--;
}

int QueueTop(Queue *q) {
  if (isQueueEmpty(q))
    return -1;

  return q->_head->_transaksi;
}

void traverseQueue(Queue *q) {
  Node *temp = q->_head;

  while (temp->_next != NULL) {
    printf("%d", temp->_transaksi);

    if (temp->_next != NULL)
      printf(" ");

    temp = temp->_next;
  }

  if (temp != NULL)
    printf("%d", temp->_transaksi);
}

int main() {
  Queue q = {0}, *p_q = &q;
  int N, S;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    int transaksi = 0;
    scanf("%d", &transaksi);

    QueuePush(p_q, transaksi);
  }

  scanf("%d", &S);
  scanf("\n");

  for (int i = 0; i < S; i++) {
    char statusTransaksi[11];
    scanf("%s", statusTransaksi);

    if (strcmp(statusTransaksi, "BERHASIL") == 0) {
      QueuePop(p_q);
    } else {
      int topqueue = QueueTop(p_q);
      QueuePop(p_q);
      QueuePush(p_q, topqueue);
    }
  }

  if (isQueueEmpty(p_q)) {
    printf("KOSONG");
  } else {
    traverseQueue(p_q);
  }
}
