#include <stdio.h>

int main() {
  int N;
  scanf("%d", &N);

  int sum = 0;
  for (int i = 0; i < N; i++) {
    printf("%d - %d\n", i, sum);

    sum += i;
  }

  return 0;
}
