#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
  int data;
  struct Node *link;
};

void Push(struct Node **stack, int x) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

  temp->data = x;
  temp->link = *stack;

  *stack = temp;
}

int Pop(struct Node **stack) {
  if (*stack == NULL)
    return -1;

  struct Node *temp;
  temp = *stack;
  *stack = (*stack)->link;

  int data_temp = temp->data;
  free(temp);

  return data_temp;
}

bool IsEmpty(struct Node *stack) { return (stack == NULL); }

int Top(struct Node *stack) {
  if (IsEmpty(stack) == false) {
    return stack->data;
  }
  return -1;
}

void FreeStack(struct Node **phead) {
  struct Node *temp = *phead;
  if (temp->link != NULL)
    FreeStack(&temp->link);

  free(temp);
}

int PerformOperation(char operand, int op1, int op2) {
  switch (operand) {
  case '+':
    return op1 + op2;
  case '-':
    return op1 - op2;
  case '*':
    return op1 * op2;
  case '/': {
    if (op2 == 0) {
      return 0;
    }

    return (int)(op1 / op2);
  }
  case '^':
    return (int)pow(op1, op2);
  }
}

int EvaluatePostFix(char **s, int len) {
  struct Node *S = NULL; // Stack init

  for (int i = 0; i < len; i++) {

    if (strcmp(s[i], "+") != 0 && strcmp(s[i], "-") != 0 &&
        strcmp(s[i], "*") != 0 && strcmp(s[i], "/") != 0 &&
        strcmp(s[i], "^") != 0) {
      Push(&S, (int)atoi(s[i]));
    }

    else if (strcmp(s[i], "+") == 0 || strcmp(s[i], "-") == 0 ||
             strcmp(s[i], "*") == 0 || strcmp(s[i], "/") == 0 ||
             strcmp(s[i], "^") == 0) {

      int op2 = Pop(&S);
      int op1 = Pop(&S);

      int res = PerformOperation(*s[i], op1, op2);
      Push(&S, res);
    }
  }

  int res = Top(S);

  FreeStack(&S);

  return res != -1 ? res : -1;
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
  char S[101];
  printf("Enter a postfix math expression : ");
  scanf("%[^\n]s", S);

  char *tokens[80];

  int i = 0;
  int *p_i = &i;
  EvaluateStringToToken(S, strlen(S), tokens, p_i);
  int res = EvaluatePostFix(tokens, i);

  printf("%d\n", res);

  for (int j = 0; j < i; j++) {
    free(tokens[j]);
  }
}
