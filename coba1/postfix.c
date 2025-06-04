#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  double data;
  struct Node *next;
};

typedef struct Node TStack;

void Push(TStack **stack, double x) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

  temp->data = x;
  temp->next = *stack;

  *stack = temp;
}

double Pop(TStack **stack) {
  if (*stack == NULL)
    return -1;

  struct Node *temp;
  temp = *stack;
  *stack = (*stack)->next;

  double data_temp = temp->data;
  free(temp);

  return data_temp;
}

bool IsEmpty(TStack *stack) { return (stack == NULL); }

double Top(TStack *stack) {
  if (IsEmpty(stack) == false) {
    return stack->data;
  }
  return -1;
}

void FreeStack(TStack **phead) {
  struct Node *temp = *phead;
  if (temp->next != NULL)
    FreeStack(&temp->next);

  free(temp);
}

double performOperation(double a, double b, char op) {
  if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else if (op == '*') {
    return a * b;
  } else if (op == '/') {
    return a / b;
  } else if (op == '^') {
    return pow(a, b);
  } else {
    return 0;
  }
}

double evaluatePostfix(char **postfixStr, int len, double x_var) {
  TStack *S = NULL;

  for (int i = 0; i < len; i++) {
    if (strcmp(postfixStr[i], "+") != 0 && strcmp(postfixStr[i], "-") != 0 &&
        strcmp(postfixStr[i], "*") != 0 && strcmp(postfixStr[i], "/") != 0 &&
        strcmp(postfixStr[i], "^") != 0) {

      if (*postfixStr[i] == 'x') {
        Push(&S, x_var);
      } else {
        Push(&S, (double)atoi(postfixStr[i]));
      }
    }

    else if (strcmp(postfixStr[i], "+") == 0 ||
             strcmp(postfixStr[i], "-") == 0 ||
             strcmp(postfixStr[i], "*") == 0 ||
             strcmp(postfixStr[i], "/") == 0 ||
             strcmp(postfixStr[i], "^") == 0) {

      double op2 = Pop(&S);
      double op1 = Pop(&S);

      double res = performOperation(op1, op2, *postfixStr[i]);
      Push(&S, res);
    }
  }

  double res = Top(S);

  FreeStack(&S);

  return res != -1 ? res : -1;
}

void evaluateStringToToken(char s[], int len, char **token, int *token_len) {
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
  double x;
  printf("Enter a postfix math expression : ");
  scanf("%[^\n]s", S);

  printf("Enter x variable : ");
  scanf(" %lf", &x);

  char *tokens[80];

  int i = 0;
  int *p_i = &i;
  evaluateStringToToken(S, strlen(S), tokens, p_i);
  double res = evaluatePostfix(tokens, i, x);

  printf("%.4lf\n", res);

  for (int j = 0; j < i; j++) {
    free(tokens[j]);
  }
  return 0;
}
