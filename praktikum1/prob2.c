/**
 * Implementasi ADT Queue (Queue menggunakan Linked List)
 *
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 *
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Struktur Node */

typedef struct queueNode_t {
  int data;
  struct queueNode_t *next;
} QueueNode;

/* Struktur ADT Queue */

typedef struct queue_t {
  QueueNode *_front, *_rear;
  unsigned _size;
} Queue;

/* Function prototype */

void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, int value);
void queue_pop(Queue *queue);
int queue_front(Queue *queue);
int queue_size(Queue *queue);

/* Function definition below */

void queue_init(Queue *queue) {
  queue->_size = 0;
  queue->_front = NULL;
  queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
  return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, int value) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode) {
    queue->_size++;
    newNode->data = value;
    newNode->next = NULL;

    if (queue_isEmpty(queue))
      queue->_front = queue->_rear = newNode;
    else {
      queue->_rear->next = newNode;
      queue->_rear = newNode;
    }
  }
}

void queue_pop(Queue *queue) {
  if (!queue_isEmpty(queue)) {
    QueueNode *temp = queue->_front;
    queue->_front = queue->_front->next;
    free(temp);

    if (queue->_front == NULL)
      queue->_rear = NULL;
    queue->_size--;
  }
}

int queue_front(Queue *queue) {
  if (!queue_isEmpty(queue)) {
    return (queue->_front->data);
  }
  return (int)0;
}

int queue_size(Queue *queue) { return queue->_size; }

int main(int argc, char const *argv[]) {
  // Buat objek QueueArray
  Queue myQueue;

  // PENTING! Jangan lupa diinisialisasi
  queue_init(&myQueue);

  int X, Y, Z;
  scanf("%d %d %d", &X, &Y, &Z);

  int currVal = 0;
  for (int i = 0; i < X; i++) {
    scanf("%d", &currVal);

    queue_push(&myQueue, currVal);
  }

  bool received = false;

  int antri_kembali = 0;
  int initialpos = X - 1;
  int updatedpos = X - 1;
  int maxPos = X - 1;
  int pos = 0;

  while (!queue_isEmpty(&myQueue)) {
    int topqueue = queue_front(&myQueue);
    if ((pos + 1) % Z == 0) {

      if (myQueue._size == 1 && pos == updatedpos && Y - topqueue > 0) {
        antri_kembali++;

        received = true;
        queue_pop(&myQueue);
        break;
      }
      queue_pop(&myQueue);
      queue_push(&myQueue, topqueue);

      if (pos != maxPos)
        antri_kembali++;

      pos++;
      maxPos++;

      updatedpos = maxPos;
    } else {

      queue_pop(&myQueue);
      if (Y - topqueue > 0 && updatedpos == pos) {
        received = true;
      }

      Y -= topqueue;
      pos++;
    }
  }

  printf("%d ", antri_kembali);
  if (received) {
    printf("YES Dapat burger gratis!!!");
  } else {
    printf("NOO tidak Dapat :(");
  }

  puts("");
  return 0;
}
