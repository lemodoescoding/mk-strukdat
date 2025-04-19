#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_NEG 0

typedef struct Node {
  char _data;
  struct Node *_next;
} StackNode;

typedef struct {
  StackNode *_top;
  size_t _size;
} Stack;

bool isStackEmpty(Stack *s) { return (s->_top == NULL); }

void StackPush(Stack *s, char ch) {
  StackNode *temp = (StackNode *)malloc(sizeof(StackNode));

  if (!temp)
    return;

  s->_size++;
  temp->_data = ch;
  temp->_next = NULL;

  if (isStackEmpty(s)) {
    s->_top = temp;
  } else {
    temp->_next = s->_top;
    s->_top = temp;
  }
}

void StackPop(Stack *s) {
  if (isStackEmpty(s))
    return;

  StackNode *temp = s->_top;
  s->_top = temp->_next;

  free(temp);
  s->_size--;
}

char StackTop(Stack *s) {
  if (isStackEmpty(s))
    return CHAR_NEG;

  return s->_top->_data;
}

int main() {
  Stack s = {0}, *p_s = &s;

  char string[100];
  scanf("%s", string);

  int lenString = strlen(string);

  for (int i = 0; i < lenString; i++) {
    StackPush(p_s, string[i]);
  }

  for (int i = 0; i < lenString; i++) {
    char char_at_top = StackTop(p_s);

    printf("%c", char_at_top);

    if (char_at_top == 'a' || char_at_top == 'i' || char_at_top == 'u' ||
        char_at_top == 'o' || char_at_top == 'e' || char_at_top == 'A' ||
        char_at_top == 'I' || char_at_top == 'U' || char_at_top == 'O' ||
        char_at_top == 'E') {
      printf("%c", char_at_top);
    }

    StackPop(p_s);
  }

  return 0;
}
