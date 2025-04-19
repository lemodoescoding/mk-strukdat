#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 20

typedef struct {
  int data[MAX_SIZE];
  int head;
  int tail;
} Queue;

void initQueue(Queue *q) {
  q->head = -1;
  q->tail = -1;
}

bool isEmptyQueue(Queue *q) { return (q->tail == -1); }
bool isFull(Queue *q) { return (q->tail == MAX_SIZE - 1); }

void enqueue(Queue *q, int val) {
  if (isEmptyQueue(q)) {
    q->head = q->tail = 0;
    q->data[q->tail] = val;
  } else {

    q->data[++(q->tail)] = val;
  }
}

int dequeue(Queue *q) {
  if (isEmptyQueue(q)) {
    printf("Queue kosong!\n");
    return -1;
  }

  int i;
  int e = q->data[q->head];

  for (i = q->head; i <= q->tail - 1; i++) {
    q->data[i] = q->data[i + 1];
  }

  q->tail--;
  return e;
}

void clearQueue(Queue *q) { q->head = q->tail = -1; }

void printQueue(Queue *q) {
  if (isEmptyQueue(q)) {
    printf("Queue kosong!\n");
    return;
  }

  printf("\n");
  for (int i = q->head; i <= q->tail; i++) {
    printf("%d", q->data[i]);

    if (i < q->tail) {
      printf(" - ");
    }
  }
}

int findElement(Queue *q, int value) {
  if (isEmptyQueue(q))
    return -1;

  for (int i = q->head; i <= q->tail; i++) {
    if (q->data[i] == value) {
      return i;
    }
  }

  return -1;
}

void editElement(Queue *q, int index, int newVal) {
  if (isEmptyQueue(q)) {
    printf("Queue kosong!");
    return;
  }

  if (index > q->tail || index < 0) {
    printf("Index out of range");
    return;
  }

  q->data[index] = newVal;
}

void calculateQueueStats(Queue *q, int *total, int *maxVal, int *minVal,
                         float *avgVal) {
  if (isEmptyQueue(q)) {
    printf("Queue Kosong!\n");
    return;
  }

  int max = q->data[q->head], min = q->data[q->head];
  int sum = 0;
  float avg = 0;

  for (int i = q->head; i <= q->tail; i++) {
    if (q->data[i] > max) {
      max = q->data[i];
    }

    if (q->data[i] < min) {
      min = q->data[i];
    }

    sum += q->data[i];
  }

  *total = sum;
  *maxVal = max;
  *minVal = min;

  *avgVal = ((float)sum / (q->tail + 1));
}

int main() {
  Queue q;
  initQueue(&q);

  enqueue(&q, 4);
  enqueue(&q, 11);
  enqueue(&q, 9);

  printQueue(&q);
  printf("\n");

  int deq = dequeue(&q);
  printf("Elemen yg sudah ter-dequeue: %d\n", deq);
  printQueue(&q);
  printf("\n");

  enqueue(&q, 5);
  enqueue(&q, 7);
  enqueue(&q, 10);

  printQueue(&q);
  printf("\n");

  int index = findElement(&q, 7);
  if (index != -1) {
    printf("Index ditemukan untuk angka 7 di index ke-%d", index);
    editElement(&q, index, 8);
  }

  printQueue(&q);

  printf("\n");
  int total, max, min;
  float avg;

  calculateQueueStats(&q, &total, &max, &min, &avg);

  printf("\nTotal: %d\nMax: %d\nMin: %d\nAvg: %f\n", total, max, min, avg);

  enqueue(&q, 14);
  enqueue(&q, 17);
  enqueue(&q, 21);

  printQueue(&q);
}
