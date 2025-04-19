#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NEG_INT -32767

typedef struct Node {
  int _data;
  struct Node *_next;
  struct Node *_prev;
} Node;

typedef struct {
  Node *_head;
  Node *_tail;
  size_t _size;
} LinkedList;

bool isLinkedListEmpty(LinkedList *ld) {
  return (ld->_head == NULL && ld->_tail == NULL);
}

void LLPushBack(LinkedList *ld, int nd) {
  Node *temp = (Node *)malloc(sizeof(Node));

  if (!temp)
    return;

  ld->_size++;
  temp->_data = nd;
  temp->_next = temp->_prev = NULL;

  if (isLinkedListEmpty(ld)) {
    ld->_head = ld->_tail = temp;
  } else {
    temp->_prev = ld->_tail;
    ld->_tail->_next = temp;
    ld->_tail = temp;
  }
}

void SwapTwoLL(LinkedList *ld, Node *n_a, Node *n_b) {
  Node *prev_a = n_a->_prev;
  Node *next_b = n_b->_next;

  Node *temp_a = n_a;
  Node *temp_b = n_b;

  if (prev_a != NULL) {
    prev_a->_next = n_b;
  }
  n_a->_prev = temp_b;
  if (next_b != NULL) {
    next_b->_prev = n_a;
  }

  n_b->_next = temp_a;
  if (next_b != NULL)
    n_a->_next = next_b;
  else
    n_a->_next = NULL;
  if (prev_a == NULL) {
    temp_b->_prev = NULL;
  } else {
    temp_b->_prev = prev_a;
  }

  if (n_a == ld->_head) {
    ld->_head = n_b;
  }

  if (n_b == ld->_tail) {
    ld->_tail = n_a;
  }
}

int main() {
  LinkedList ld = {0}, *p_ld = &ld;
  int N;
  scanf("%d", &N);

  int currVal = 0;
  for (int i = 0; i < N; i++) {
    scanf("%d", &currVal);

    LLPushBack(p_ld, currVal);
  }

  int swapCount = N / 2;
  int isEven = (N % 2 == 0);

  Node *temp = p_ld->_head;

  Node *n_a = temp;
  Node *n_b = temp->_next;

  for (int i = 0; i < swapCount; i++) {
    if (isEven && i == swapCount - 1)
      break;
    SwapTwoLL(p_ld, n_a, n_b);
    n_a = n_a->_next;
    n_b = n_a->_next;
  }

  if (isEven) {
    SwapTwoLL(p_ld, n_a, n_b);
  }

  temp = p_ld->_head;
  for (int i = 0; i < N; i++) {
    printf("%d", temp->_data);

    temp = temp->_next;

    if (i + 1 < N) {
      printf(" ");
    }
  }
}
