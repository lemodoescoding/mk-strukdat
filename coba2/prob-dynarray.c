#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_ARR_SIZE 16
#define NEG_INT -32767

typedef struct Array {
  int *_items;
  size_t _count;
  size_t _capacity;
} DynamicArray;

bool isDynArrayEmpty(DynamicArray *da) { return (da->_count == 0); }

void DnPushBack(DynamicArray *da, int nd) {
  if (da->_count + 1 > da->_capacity) {
    if (da->_capacity == 0)
      da->_capacity = 16;
    else
      da->_capacity *= 2;
    da->_items = realloc(da->_items, da->_capacity * sizeof(da->_items));
  }

  da->_items[da->_count++] = nd;
}

void DnPopBack(DynamicArray *da) {
  if (isDynArrayEmpty(da))
    return;

  da->_count--;
}

int DnBack(DynamicArray *da) {
  if (isDynArrayEmpty(da))
    return NEG_INT;

  return da->_items[da->_count - 1];
}

int DnFront(DynamicArray *da) {
  if (isDynArrayEmpty(da))
    return NEG_INT;

  return da->_items[0];
}

void DnSetAt(DynamicArray *da, size_t i, int nd) {
  if (isDynArrayEmpty(da))
    return;

  if (i < da->_count)
    da->_items[i] = nd;
}

int DnGetAt(DynamicArray *da, size_t i) {
  if (isDynArrayEmpty(da))
    return NEG_INT;

  if (i < da->_count)
    return da->_items[i];
  else
    return NEG_INT;
}

void DnFree(DynamicArray *da) {
  free(da->_items);
  da->_count = 0;
  da->_capacity = 0;
}

int compareValue(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int absValue(int a) { return (a >= 0) ? a : -a; }

int main() {
  int T = 1;
  scanf("%d", &T);

  DynamicArray L[T], *p_L = L;
  DynamicArray J[T], *p_J = J;
  int results[T];

  for (int i = 0; i < T; i++) {
    L[i]._count = 0;
    L[i]._capacity = 0;
    L[i]._items = NULL;

    int tempVal = 0;
    while (true) {
      scanf("%d", &tempVal);

      DnPushBack(&L[i], tempVal);

      if (tempVal == -1)
        break;
    }

    J[i]._count = 0;
    J[i]._capacity = 0;
    J[i]._items = NULL;

    while (true) {
      scanf("%d", &tempVal);

      DnPushBack(&J[i], tempVal);

      if (tempVal == -1)
        break;
    }

    qsort(L[i]._items, L[i]._count, sizeof(L[i]._items[0]), compareValue);
    qsort(J[i]._items, J[i]._count, sizeof(J[i]._items[0]), compareValue);

    int left = 0;
    int right = J[i]._count - 1;

    int total_diff = 0;

    for (int j = 0; j < J[i]._count; j++) {
      int diff_left = absValue(L[i]._items[j] - J[i]._items[left]);
      int diff_right = absValue(L[i]._items[j] - J[i]._items[right]);

      if (diff_left > diff_right) {
        total_diff += diff_left;
        left += 1;
      } else {
        total_diff += diff_right;
        right -= 1;
      }
    }

    results[i] = total_diff;
  }

  for (int i = 0; i < T; i++)
    printf("%d\n", results[i]);
}
