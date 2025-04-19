#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int _data;
  struct Node *_next;
} SNode;

typedef struct {
  SNode *_top;
  size_t _size;
} ModStack;

bool isEmpty(ModStack *st) { return (st->_top == NULL); }

int Top(ModStack *st) {
  if (isEmpty(st))
    return 0;

  return st->_top->_data;
}

void Push(ModStack *st, int nd) { // just do regular push procedure into a stack
  SNode *temp = (SNode *)malloc(sizeof(SNode));

  if (temp) {
    temp->_data = nd;

    if (isEmpty(st)) {
      temp->_next = NULL;
      st->_top = temp;
    } else {
      temp->_next = st->_top;
      st->_top = temp;
    }

    st->_size++;
  }
}

void PushElem(ModStack *st, ModStack *ast, int nd) {
  Push(st, nd); // Push into the real stack

  // below is for determining the smallest entry every time when this function
  // is called
  if (isEmpty(ast)) {
    Push(ast, nd);
  } else if (nd < Top(ast)) {
    Push(ast, nd);
  } else {
    Push(ast, Top(ast));
  }
}

SNode *Pop(ModStack *st) { // regular pop procedure
  if (isEmpty(st))
    return NULL;

  struct Node *temp = st->_top;
  st->_top = st->_top->_next;
  st->_size--;

  return temp;
}

void PopElem(ModStack *st, ModStack *ast) {
  // when popping an element, the entries on top of the stack on both
  // *st and *ast is removed, hence this will update the current minimun value
  // of the entries entry of the stack

  if (isEmpty(st))
    return;

  SNode *temp = Pop(st);

  if (temp) {
    free(Pop(ast));
  }

  free(temp);
}

int Smallest(ModStack *st) { return Top(st); }

int main() {

  ModStack xs = {0};
  ModStack xst = {0};

  int x;
  do {
    printf("Input a number: ");

    scanf("%d", &x);

    PushElem(&xs, &xst, x);

    printf("Smallest elem: %d\n", Smallest(&xst));

    char ch;
    printf("Continue? ");

    scanf(" %c", &ch);

    if (ch == 'N')
      break;
  } while (1);
  return 0;
}
