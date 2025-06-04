#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// FORMAL DEFINITION OF STACK

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

// INFIX TO POSTFIX SECTION

bool HasHigherPrec(char a, char b) {
  if ((a == '*' && b == '+') || (a == '*' && b == '-')) {
    return true;
  } else if ((a == '/' && b == '+') || (a == '/' && b == '-')) {
    return true;
  } else if ((a == '+' && b == '-') || (a == '*' && b == '/')) {
    return true;
  } else if (a == b) {
    return true;
  } else {
    return false;
  }
}

bool IsOpeningParentheses(char a) { return (a == '(') ? true : false; }

bool IsClosingParentheses(char a) { return (a == ')') ? true : false; }

void EvaluateTokenToPostFix(char **s, int len) {
  struct Node *S = NULL;

  char *postFix[80];
  int j = 0;

  for (int i = 0; i < len; i++) {
    if (strcmp(s[i], "+") != 0 && strcmp(s[i], "-") != 0 &&
        strcmp(s[i], "*") != 0 && strcmp(s[i], "/") != 0 &&
        strcmp(s[i], "^") != 0 && !IsOpeningParentheses(*s[i]) &&
        !IsClosingParentheses(*s[i])) {

      char *temp = (char *)malloc(sizeof(char) * strlen(s[i]));

      postFix[j] = temp;
      strcpy(postFix[j], s[i]);

      j++;

    } else if (strcmp(s[i], "+") == 0 || strcmp(s[i], "-") == 0 ||
               strcmp(s[i], "*") == 0 || strcmp(s[i], "/") == 0 ||
               strcmp(s[i], "^") == 0) {

      while (!IsEmpty(S) && HasHigherPrec((char)Top(S), (char)*s[i]) &&
             !IsOpeningParentheses((char)Top(S))) {
        char op = (char)Top(S);

        char *temp = (char *)malloc(sizeof(char) * 2);
        postFix[j] = temp;

        postFix[j][0] = op;
        postFix[j][1] = '\0';

        Pop(&S);

        j++;
      }

      char op = (char)*s[i];
      Push(&S, op);

    } else if (IsOpeningParentheses(*s[i]) == true) {
      char pr = (char)*s[i];

      Push(&S, pr);

    } else if (IsClosingParentheses(*s[i]) == true) {
      while (!IsEmpty(S) && !IsOpeningParentheses(Top(S))) {
        char pr = (char)Top(S);

        char *temp = (char *)malloc(sizeof(char) * 2);
        postFix[j] = temp;
        postFix[j][0] = pr;
        postFix[j][1] = '\0';

        j++;

        Pop(&S);
      }

      while (IsOpeningParentheses(Top(S))) {
        Pop(&S);
      }
    }
  }

  while (!IsEmpty(S)) {
    char op = (char)Top(S);
    char *temp = (char *)malloc(sizeof(char) * 2);
    postFix[j] = temp;

    postFix[j][0] = op;
    postFix[j][1] = '\0';

    Pop(&S);

    j++;
  }

  printf("\n");

  for (int k = 0; k < j; k++) {
    printf("%s ", postFix[k]);
  }

  for (int k = 0; k < j; k++) {
    free(postFix[k]);
  }
}

// CONVERT STRING TO INDIVIDUAL TOKENS

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

int main(void) {
  char s[101];
  printf("Enter a valid math expression without equal sign: ");
  scanf("%[^\n]s", s);

  char *tokens[100] = {0};

  int i = 0;
  int *p_i = &i;

  EvaluateStringToToken(s, strlen(s), tokens, p_i);
  EvaluateTokenToPostFix(tokens, i);

  return 0;
}
