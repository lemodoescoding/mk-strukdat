#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct graph {
  long vertexCount, edgeCount;
  vector<vector<long>> adjList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;

    for (int i = 0; i < vertexCount; i++) {
      adjList.push_back({}); // inserts V ammount of empty vector
    }
  }

  void add_edge(long vertex1, long vertex2) {
    adjList[vertex1].push_back(vertex2);
    adjList[vertex2].push_back(vertex1);
    edgeCount++;
  }

  void bfs(vector<long> &result, long start, long L) {
    vector<bool> visited(vertexCount, false);
    queue<long> q;

    vector<int> dist(vertexCount, INT_MAX);

    q.push(start);
    visited[start] = true;
    result.push_back(start);

    dist[start] = 0;

    while (!q.empty()) {
      long temp = q.front();
      q.pop();

      for (auto vertex : adjList[temp]) {
        if (!visited[vertex]) {
          q.push(vertex);
          visited[vertex] = true;
          result.push_back(vertex);

          dist[vertex] = dist[temp] + 1;
        }
      }
    }

    bool found = false;
    for (int i = 0; i < vertexCount; i++) {
      if (dist[i] == L) {

        cout << i << endl;
        found = true;
      }
    }

    if (found == false)
      cout << "Not Found" << endl;
  }
};

int main() {
  int N, M, L;
  cin >> N;
  cin >> M;
  cin >> L;

  int S;
  cin >> S;

  graph g;
  g.init(N);

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u;
    cin >> v;

    g.add_edge(u, v);
  }
  vector<long> bfs_result;

  g.bfs(bfs_result, S, (long)L);

  return 0;
}
