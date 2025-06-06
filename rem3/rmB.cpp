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
      adjList.push_back({});
    }
  }

  void add_edge(long vertex1, long vertex2) {
    adjList[vertex1].push_back(vertex2);
    adjList[vertex2].push_back(vertex1);
    edgeCount++;
  }

  long bfs(vector<long> &result, long start, long end) {
    vector<bool> visited(vertexCount, false);
    queue<long> q;

    vector<long> dist(vertexCount, 0);

    q.push(start);
    visited[start] = true;
    result.push_back(start);

    vector<long> final_dist(vertexCount, 0);

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

          if (vertex == end) {
            return dist[vertex];
          }
        }
      }
    }

    return -1;
  }
};

int main() {
  long N, M, S, T;
  cin >> N;
  cin >> M;
  cin >> S;
  cin >> T;

  graph g;
  g.init(N);

  for (int i = 0; i < M; i++) {
    long u, v;
    cin >> u;
    cin >> v;

    g.add_edge(u, v);
  }

  vector<long> result;
  cout << g.bfs(result, S, T) << endl;
}
