#include <stdio.h>
#include <stdlib.h>

typedef struct tipeS {
  struct tipeS *left, *right;
  int info;
} Simpul;

Simpul *P, *FIRST, *LAST, *PVertex, *PEdge, *Q, *R, *S;
Simpul *PointS[5];

int main() {
  int A[5][5] = {{0, 5, 0, 2, 0},
                 {6, 0, 3, 0, 0},
                 {0, 0, 0, 0, 9},
                 {0, 0, 12, 0, 7},
                 {0, 14, 0, 0, 0}};

  char NmS[5] = {'A', 'B', 'C', 'D', 'E'};
  int i, j;

  i = 0;
  P = (Simpul *)malloc(sizeof(Simpul));
  P->info = NmS[0];

  FIRST = LAST = P;
  P->left = P->right = NULL;
  PointS[0] = P;

  printf("%c alamat %p\n", P->info, (void *)PointS[0]);

  for (i = 1; i < 5; i++) {
    P = (Simpul *)malloc(sizeof(Simpul));
    P->info = NmS[i];
    LAST->left = P;
    LAST = LAST->left;

    P->left = NULL;
    P->right = NULL;
    PointS[i] = P;

    printf("%c alamat %p\n", P->info, (void *)PointS[i]);
  }

  Q = FIRST;
  for (i = 0; i < 5; i++) {
    R = Q;
    printf("Vertex %c ... \n", Q->info);
    for (j = 0; j < 5; j++) {
      if (A[i][j] != 0) {
        P = (Simpul *)malloc(sizeof(Simpul));
        P->info = A[i][j];
        R->right = P;
        P->left = PointS[j];

        printf("berhubungan dengan %c bobot %d\n", P->left->info, P->info);

        P->right = NULL;
        R = P;
      }
    }

    printf("\n");
    Q = Q->left;
  }
}
