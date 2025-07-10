#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
  int x, y;
} Person;

typedef struct QuadTreeNode {
  int x_min, y_min, x_max, y_max;
  Person *person;
  struct QuadTreeNode *child[4];
} QuadTreeNode;

Person *createPerson(int x, int y) {
  Person *person = (Person *)malloc(sizeof(Person));
  person->x = x;
  person->y = y;

  return person;
}

QuadTreeNode *createNode(int x_min, int y_min, int x_max, int y_max) {
  QuadTreeNode *temp = (QuadTreeNode *)malloc(sizeof(QuadTreeNode));
  temp->x_max = x_max;
  temp->y_max = y_max;
  temp->x_min = x_min;
  temp->y_min = y_min;

  temp->person = NULL;
  for (int i = 0; i < 4; i++)
    temp->child[i] = NULL;

  return temp;
}

int determineQuadrant(QuadTreeNode *qt, Person *p) {
  int cx = (qt->x_min + qt->x_max) / 2;
  int cy = (qt->y_min + qt->y_max) / 2;

  if (p->x < cx && p->y >= cy)
    return 0; // NW
  if (p->x >= cx && p->y >= cy)
    return 1; // NE
  if (p->x < cx && p->y < cy)
    return 2; // SW
  return 3;   // SE
}

void subdivide(QuadTreeNode *qt) {
  int cx = (qt->x_min + qt->x_max) / 2;
  int cy = (qt->y_min + qt->y_max) / 2;

  qt->child[0] = createNode(qt->x_min, cy, cx, qt->y_max);
  qt->child[1] = createNode(cx, cy, qt->x_max, qt->y_max);
  qt->child[2] = createNode(qt->x_min, qt->y_min, cx, cy);
  qt->child[3] = createNode(cx, qt->y_min, qt->x_max, cy);
}

void insertNode(QuadTreeNode *qt, Person *p) {
  if (qt->child[0] == NULL) {
    if (qt->person == NULL) {
      qt->person = p;
      return;
    } else {
      Person *person_existing = qt->person;
      qt->person = NULL;

      subdivide(qt);
      insertNode(qt, person_existing);
      insertNode(qt, p);
    }
  } else {
    int quadrant = determineQuadrant(qt, p);

    insertNode(qt->child[quadrant], p);
  }
}

int countRooms(QuadTreeNode *qt) {
  if (qt == NULL)
    return 0;
  if (qt->child[0] == NULL)
    return 1;

  int total = 0;
  for (int i = 0; i < 4; i++)
    total += countRooms(qt->child[i]);

  return total;
}

void freeTree(QuadTreeNode *qt) {
  if (qt == NULL)
    return;
  for (int i = 0; i < 4; i++)
    freeTree(qt->child[i]);

  if (qt->person)
    free(qt->person);
  free(qt);
}

int main() {
  int N;
  scanf("%d", &N);

  Person *persons[N];

  for (int i = 0; i < N; i++) {
    int X, Y;
    scanf("%d %d", &X, &Y);

    persons[i] = createPerson(X, Y);
  }

  QuadTreeNode *qt = createNode(-100, -100, 100, 100);

  for (int i = 0; i < N; i++)
    insertNode(qt, persons[i]);

  int room_count = countRooms(qt);
  printf("%d", room_count);

  freeTree(qt);

  return 0;
}
