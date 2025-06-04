#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
  int dest;
  int weight;
  struct AdjNode *next;
} AdjNode;

typedef struct AdjList {
  AdjNode *head;
} AdjList;

typedef struct Graph {
  int V;
  AdjList *array;
} Graph;

AdjNode *newAdjNode(int dest, int weight) {
  AdjNode *temp = (AdjNode *)malloc(sizeof(AdjNode));
  temp->dest = dest;
  temp->weight = weight;
  temp->next = NULL;

  return temp;
}

Graph *createGraph(int V) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->V = V;
  graph->array = (AdjList *)malloc(V * sizeof(AdjList));
  for (int i = 0; i < V; ++i)
    graph->array[i].head = NULL;
  return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight) {
  AdjNode *newNode = newAdjNode(dest, weight);
  if (graph->array[src].head == NULL) {

    graph->array[src].head = newNode;
  } else {
    AdjNode *temp = graph->array[src].head;
    while (temp->next != NULL) {
      temp = temp->next;
    }

    temp->next = newNode;
  }

  newNode = newAdjNode(src, weight);
  if (graph->array[dest].head == NULL) {

    graph->array[dest].head = newNode;
  } else {
    AdjNode *temp = graph->array[dest].head;

    while (temp->next != NULL) {
      temp = temp->next;
    }

    temp->next = newNode;
  }
}

void deleteEdge(Graph *graph, int src, int dest) {
  struct AdjNode *temp = graph->array[src].head;
  struct AdjNode *prev = NULL;

  while (temp != NULL && temp->dest != dest) {
    prev = temp;
    temp = temp->next;
  }
  if (temp != NULL) {
    if (prev != NULL)
      prev->next = temp->next;
    else
      graph->array[src].head = temp->next;
    free(temp);
  }

  temp = graph->array[dest].head;
  prev = NULL;
  while (temp != NULL && temp->dest != src) {
    prev = temp;
    temp = temp->next;
  }
  if (temp != NULL) {
    if (prev != NULL)
      prev->next = temp->next;
    else
      graph->array[dest].head = temp->next;
    free(temp);
  }
}

int searchEdge(Graph *graph, int src, int dest) {
  struct AdjNode *temp = graph->array[src].head;
  while (temp != NULL) {
    if (temp->dest == dest)
      return 1; // Found
    temp = temp->next;
  }
  return 0; // Not Found
}

void DFSUtil(int v, int visited[], Graph *graph) {
  visited[v] = 1;
  printf("%d ", v);

  struct AdjNode *temp = graph->array[v].head;
  while (temp) {
    int adjVertex = temp->dest;
    if (!visited[adjVertex])
      DFSUtil(adjVertex, visited, graph);
    temp = temp->next;
  }
}

void DFS(Graph *graph, int startVertex) {
  int *visited = (int *)malloc(graph->V * sizeof(int));
  for (int i = 0; i < graph->V; i++)
    visited[i] = 0;

  DFSUtil(startVertex, visited, graph);
  free(visited);
}

void BFS(Graph *graph, int startVertex) {
  int *visited = (int *)malloc(graph->V * sizeof(int));
  for (int i = 0; i < graph->V; i++)
    visited[i] = 0;

  int *queue = (int *)malloc(graph->V * sizeof(int));
  int front = 0;
  int rear = 0;

  visited[startVertex] = 1;
  queue[rear++] = startVertex;

  while (front < rear) {
    int currentVertex = queue[front++];
    printf("%d ", currentVertex);

    struct AdjNode *temp = graph->array[currentVertex].head;
    while (temp) {
      int adjVertex = temp->dest;
      if (!visited[adjVertex]) {
        visited[adjVertex] = 1;
        queue[rear++] = adjVertex;
      }
      temp = temp->next;
    }
  }

  free(queue);
  free(visited);
}

int main() {
  int V = 5;
  Graph *graph = createGraph(V);

  addEdge(graph, 0, 1, 10);
  addEdge(graph, 0, 2, 20);
  addEdge(graph, 0, 3, 30);
  addEdge(graph, 1, 3, 40);
  addEdge(graph, 1, 4, 50);

  printf("Following is Depth First Traversal (starting "
         "from vertex 0)\n");
  DFS(graph, 0);

  printf("\nFollowing is Breadth First Traversal "
         "(starting from vertex 0)\n");
  BFS(graph, 0);

  printf("\nSearching for edge 1-3: %s\n",
         searchEdge(graph, 1, 3) ? "Found" : "Not Found");
  deleteEdge(graph, 1, 3);

  printf("Searching for edge 1-3 after deletion: %s\n",
         searchEdge(graph, 1, 3) ? "Found" : "Not Found");

  return 0;
}
