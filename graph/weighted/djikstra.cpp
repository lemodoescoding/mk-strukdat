#include <bits/stdc++.h>
using namespace std;

struct graph {
  long vertexCount, edgeCount;
  vector<vector<pair<long, long>>> adjList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;

    for (int i = 0; i < vertexCount; i++) {
      adjList.push_back({}); // inserts V ammount of empty vector
    }
  }

  void add_edge(long vertex1, long vertex2, long weight) {
    adjList[vertex1].push_back(make_pair(vertex2, weight));
    adjList[vertex2].push_back(make_pair(vertex1, weight));
    edgeCount++;
  }

  void dfs(vector<long> &result, long start) {
    vector<bool> visited(vertexCount, false);
    stack<long> st;

    st.push(start);
    visited[start] = true;
    result.push_back(start);

    while (!st.empty()) {
      long temp = st.top();
      st.pop();

      if (!visited[temp]) {
        result.push_back(temp);
        visited[temp] = true;
      }

      for (auto vertex : adjList[temp]) {
        if (!visited[vertex.first])
          st.push(vertex.first);
      }
    }
  }

  void bfs(vector<long> &result, long start) {
    vector<bool> visited(vertexCount, false);
    queue<long> q;

    q.push(start);
    visited[start] = true;
    result.push_back(start);

    while (!q.empty()) {
      long temp = q.front();
      q.pop();

      for (auto vertex : adjList[temp]) {
        if (!visited[vertex.first]) {
          q.push(vertex.first);
          visited[vertex.first] = true;
          result.push_back(vertex.first);
        }
      }
    }
  }

  void dijkstra(vector<long> &result, vector<long> &prev, long start) {
    vector<bool> visited(vertexCount, false);
    priority_queue<pair<long, long>, vector<pair<long, long>>,
                   greater<pair<long, long>>>
        pq;
    result = vector<long>(vertexCount, LONG_MAX);
    prev = vector<long>(vertexCount, -1);

    pq.push(make_pair(0, start));
    result[start] = 0;

    while (!pq.empty()) {
      auto temp = pq.top();
      pq.pop();

      visited[temp.second] = true;

      for (auto vertex : adjList[temp.second]) {
        long nextVertex = vertex.first;
        long weight = vertex.second;

        if (!visited[nextVertex]) {
          if (temp.first + weight < result[nextVertex]) {
            result[nextVertex] = temp.first + weight;
            prev[nextVertex] = temp.second;
            pq.push(make_pair(result[nextVertex], nextVertex));
          }
        }
      }
    }
  }

  void printPath(long end, const vector<long> &prev) {
    if (prev[end] == -1) {
      cout << end;
      return;
    }

    printPath(prev[end], prev);
    cout << " -> " << end;
  }
};

int main() {
  graph g;
  g.init(5);
  g.add_edge(0, 1, 4);
  g.add_edge(0, 2, 1);
  g.add_edge(2, 1, 2);
  g.add_edge(1, 3, 1);
  g.add_edge(3, 4, 3);

  vector<long> dist, prev;
  g.dijkstra(dist, prev, 0);

  cout << "Distance to 4: " << dist[4] << endl;
  cout << "Path: ";
  g.printPath(4, prev);
  cout << endl;
  return 0;
}
