#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void insertEdge(int **graph, int u, int v, int weight) {
  *(*(graph + u) + v) = weight;
  *(*(graph + v) + u) = weight;
}

void deleteEdge(int **graph, int u, int v) {
  *(*(graph + u) + v) = 0;
  *(*(graph + v) + u) = 0;
}

int searchEdge(int **graph, int u, int v) { return *(*(graph + u) + v); }

void BFS(int **graph, int start) {
  bool visited[MAX] = {0};
  int queue[MAX], front = 0, rear = 0;

  visited[start] = true;
  queue[rear++] = start;

  while (front < rear) {
    int current = queue[front++];
    printf("%d ", current);

    for (int i = 0; i < MAX; i++) {
      if (*(*(graph + current) + i) >= 1 && !visited[i]) {
        visited[i] = true;
        queue[rear++] = i;
      }
    }
  }

  printf("\n");
}

void DFSUtil(int **graph, int start, bool *visited) {
  visited[start] = true;

  printf("%d ", start);

  for (int i = 0; i < MAX; i++) {
    if (*(*(graph + start) + i) >= 1 && !*(visited + i)) {
      DFSUtil(graph, i, visited);
    }
  }
}

void DFS(int **graph, int start) {
  bool *visited = (bool *)calloc(MAX, sizeof(bool));

  DFSUtil(graph, start, visited);

  printf("\n");
}

int main() {
  // Initialize adjacency matrix to 0
  //
  int **graph = (int **)malloc(sizeof(int *) * MAX);
  for (int i = 0; i < MAX; i++) {
    graph[i] = (int *)calloc(MAX, sizeof(int));

    for (int j = 0; j < MAX; j++) {
      graph[i][j] = 0;
    }
  }

  // Add edges
  insertEdge(graph, 0, 1, 10);
  insertEdge(graph, 0, 2, 20);
  insertEdge(graph, 0, 3, 30);
  insertEdge(graph, 1, 3, 40);
  insertEdge(graph, 1, 4, 50);

  // Perform BFS
  printf("BFS starting from node 2:\n");
  BFS(graph, 0);

  // Perform DFS
  printf("DFS starting from node 2:\n");
  DFS(graph, 0);

  for (int i = 0; i < MAX; i++) {
    free(graph[i]);
  }

  return 0;
}
