#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int _data;
  struct Node *_next;
} SNode;

typedef struct {
  SNode *_top;
  size_t _size;
} Stack;

bool isEmpty(Stack *st) { return (st->_top == NULL); }

int Top(Stack *st) {
  if (isEmpty(st))
    return 0;

  return st->_top->_data;
}

void Push(Stack *st, int nd) { // just do regular push procedure into a stack
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

SNode *Pop(Stack *st) { // regular pop procedure
  if (isEmpty(st))
    return NULL;

  struct Node *temp = st->_top;
  st->_top = st->_top->_next;
  st->_size--;

  return temp;
}

void EvaluateStringToToken(char s[], int len, char **token, int *token_len) {
  char *t = strtok(s, " ");

  int i = 0;
  while (t != NULL) {

    token[i] = malloc(strlen(t) + 1);
    strcpy(token[i], t);

    t = strtok(NULL, " ");

    i++;
  }

  *token_len = i;
}

int main() {
  Stack xs = {0}, *p_xs = &xs;
  char str[1001];

  scanf("%[^\n]", str);

  char *tokens[1001] = {0};

  int len = 0;
  int *p_len = &len;

  EvaluateStringToToken(str, strlen(str), tokens, p_len);

  for (int i = 0; i < len; i++) {
    if (strcmp(tokens[i], "C") == 0) {
      Pop(p_xs);

    } else if (strcmp(tokens[i], "D") == 0) {
      int top_temp = Top(p_xs);

      Push(p_xs, top_temp * 2);
    } else if (strcmp(tokens[i], "+") == 0) {
      int top_temp = Top(p_xs);
      Pop(p_xs);

      int top_temp2 = Top(p_xs);

      Push(p_xs, top_temp);
      Push(p_xs, top_temp + top_temp2);
    } else {
      Push(p_xs, atoi(tokens[i]));
    }
  }

  int res = 0;
  while (!isEmpty(p_xs)) {
    int top_temp = Top(p_xs);

    res += top_temp;

    Pop(p_xs);
  }

  printf("%d\n", res);
  return 0;
}
