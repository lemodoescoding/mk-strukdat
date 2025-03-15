#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int _data;
  struct Node *_next;
};

typedef struct Node TNode;

typedef struct SList {
  size_t _size;
  TNode *_head;
} SLL;

bool isSLLEmpty(SLL *sl) { return (sl->_head == NULL); }

void pushBack(SLL *sl, int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  if (temp) {
    sl->_size++;
    temp->_data = nd;
    temp->_next = NULL;

    if (isSLLEmpty(sl)) {
      sl->_head = temp;
    } else {
      TNode *help = sl->_head;

      while (help->_next != NULL)
        help = help->_next;

      help->_next = temp;
    }
  }
}

void pushFront(SLL *sl, int nd) {
  TNode *temp = (TNode *)malloc(sizeof(TNode));
  if (temp) {
    sl->_size++;
    temp->_data = nd;

    if (isSLLEmpty(sl)) {
      temp->_next = NULL;
    } else {
      temp->_next = sl->_head;
    }

    sl->_head = temp;
  }
}

void insertAt(SLL *sl, int index, int nd) {
  if (isSLLEmpty(sl) || index >= sl->_size) {
    pushBack(sl, nd);
    return;
  } else if (index == 0) {
    pushFront(sl, nd);
    return;
  }

  TNode *temp = (TNode *)malloc(sizeof(TNode));

  if (temp) {
    TNode *help = sl->_head;
    temp->_data = nd;
    int _i = 0;

    while (help->_next != NULL && _i < index - 1) {
      help = help->_next;
      _i++;
    }

    temp->_next = help->_next;
    help->_next = temp;
    sl->_size++;
  }
}

int back(SLL *sl) {
  if (isSLLEmpty(sl))
    return 0;

  TNode *help = sl->_head;

  while (help->_next != NULL) {
    help = help->_next;
  }

  return help->_data;
}

int front(SLL *sl) {
  if (isSLLEmpty(sl))
    return 0;

  return sl->_head->_data;
}

int getAt(SLL *sl, int index) {
  if (isSLLEmpty(sl))
    return 0;

  TNode *help = sl->_head;

  int _i = 0;
  while (help->_next != NULL && _i < index) {
    _i++;
    help = help->_next;
  }

  return help->_data;
}

void popBack(SLL *sl) {
  if (isSLLEmpty(sl))
    return;

  TNode *curr = sl->_head;
  TNode *next = sl->_head->_next;

  if (next == NULL) {
    free(curr);
    sl->_size--;
    sl->_head = NULL;
    return;
  }

  while (curr->_next != NULL) {
    curr = next;
    next = next->_next;
  }

  curr->_next = NULL;
  free(next);
  sl->_size--;
}

void popFront(SLL *sl) {
  if (isSLLEmpty(sl))
    return;

  TNode *help = sl->_head;

  if (sl->_head->_next == NULL) {
    free(help);
    sl->_head = NULL;
    sl->_size--;
    return;
  }

  sl->_head = help->_next;
  free(help);
  sl->_size--;
}

void removeL(SLL *sl, int x) {
  if (isSLLEmpty(sl))
    return;

  TNode *help = sl->_head;
  TNode *prev;

  if (help->_data == x) {
    popFront(sl);
    return;
  }

  while (help != NULL && help->_data != x) {
    prev = help;
    help = help->_next;
  }

  if (help == NULL)
    return;

  prev->_next = help->_next;
  free(help);
  sl->_size--;
}

void freeLL(SLL *sl) {
  if (isSLLEmpty(sl))
    return;

  TNode *temp = sl->_head;
  TNode *curr;

  while (temp != NULL) {
    curr = temp;
    temp = temp->_next;

    free(curr);
  }
}

int main() {
  SLL xs = {0};

  pushFront(&xs, 2);
  pushFront(&xs, 3);
  pushFront(&xs, 5);
  pushFront(&xs, 7);
  pushFront(&xs, 11);
  pushBack(&xs, -2);

  TNode *curr = xs._head;

  for (size_t i = 0; i < xs._size; ++i) {
    printf("%d\n", curr->_data);
    curr = curr->_next;
  }
  printf("\n\n");

  curr = xs._head;

  insertAt(&xs, 3, 17);
  for (size_t i = 0; i < xs._size; ++i) {
    printf("%d\n", curr->_data);
    curr = curr->_next;
  }
  printf("\n\n");

  curr = xs._head;
  removeL(&xs, 5);

  for (size_t i = 0; i < xs._size; ++i) {
    printf("%d\n", curr->_data);
    curr = curr->_next;
  }
  curr = xs._head;

  freeLL(&xs);
  return 0;
}
