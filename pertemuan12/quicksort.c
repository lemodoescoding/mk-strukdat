#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void printArray(int *arr, int size) {
  printf("Sorted Array: \n");

  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);

    if (i + 1 < size) {
      printf(" ");
    }
  }

  printf("\n");
}

int partition(int *arr, int lo, int hi) {
  int pivot = arr[hi];

  int i = lo - 1;

  for (int j = lo; j <= hi - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[hi]);

  return i + 1;
}

void quicksort(int *arr, int lo, int hi, int size) {

  printf("Hi: %d - Lo: %d ", arr[hi], arr[lo]);

  if (lo >= hi)
    printf("\n");

  if (lo < hi) {
    int pi = partition(arr, lo, hi);

    printf(" Pivot: %d\n", pi);

    printArray(arr, size);

    quicksort(arr, lo, pi - 1, size);
    quicksort(arr, pi + 1, hi, size);
  }
}

int main(void) {

  int c;
  scanf("%d", &c);

  int arr[c];
  for (int i = 0; i < c; i++) {
    scanf("%d", &arr[i]);
  }

  quicksort(arr, 0, c - 1, sizeof(arr) / sizeof(arr[0]));

  printArray(arr, sizeof(arr) / sizeof(arr[0]));

  return 0;
}
