#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct DynArray {
  int *_items;
  size_t _count;
  size_t _capacity;
};

typedef struct DynArray DNumbers;
typedef struct DynArray DChars; // just threat chars like integers

bool isDynEmpty(struct DynArray *dn) { return (dn->_count == 0); }

void pushBack(DNumbers *dn, int nd) {
  if (dn->_count + 1 > dn->_capacity) {

    if (dn->_capacity == 0)
      dn->_capacity = 16;
    else
      dn->_capacity *= 2;

    dn->_items = realloc(dn->_items, dn->_capacity * sizeof(dn->_items));
  }

  dn->_items[dn->_count++] = nd;
}

void popBack(struct DynArray *dn) {
  if (isDynEmpty(dn))
    return;

  dn->_count--;
}

int back(struct DynArray *dn) {
  if (isDynEmpty(dn))
    return -1;

  return dn->_items[dn->_count - 1];
}

int front(struct DynArray *dn) {
  if (isDynEmpty(dn))
    return -1;

  return dn->_items[0];
}

void setAt(struct DynArray *dn, size_t i, int nd) {
  if (isDynEmpty(dn))
    return;

  if (i >= dn->_count)
    dn->_items[dn->_count - 1] = nd;
  else
    dn->_items[i] = nd;
}

int getAt(struct DynArray *dn, size_t i) {
  if (isDynEmpty(dn))
    return -1;

  if (i >= dn->_count)
    return dn->_items[dn->_count - 1];
  else
    return dn->_items[i];
}

void freeDynArray(struct DynArray *dn) {
  free(dn->_items);
  dn->_count = 0;
  dn->_capacity = 0;
}

int main() {
  DNumbers xs = {0};

  pushBack(&xs, 2);
  pushBack(&xs, 3);
  pushBack(&xs, 4);
  popBack(&xs);
  pushBack(&xs, 5);
  pushBack(&xs, 6);

  for (size_t i = 0; i < xs._count; ++i)
    printf("%d\n", xs._items[i]);

  printf("%d\n", back(&xs));

  printf("%d\n", getAt(&xs, 2));
  setAt(&xs, 2, 10);
  printf("%d\n", getAt(&xs, 2));

  freeDynArray(&xs);
  return 0;
}
