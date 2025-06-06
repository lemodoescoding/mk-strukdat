#include <algorithm>
#include <climits>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

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
    cout << " - " << end;
  }
};

int main() {
  long A, B;
  cin >> A;
  cin >> B;

  graph g;
  g.init(A);

  for (int i = 0; i < B; i++) {
    long v1, v2, w;

    cin >> v1;
    cin >> v2;
    cin >> w;

    g.add_edge(v1, v2, w);
  }

  long N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    long S;
    cin >> S;

    if (S >= A) {
      cout << "\nInvalid starting point" << endl;
      continue;
    }

    vector<long> dist, prev;

    g.dijkstra(dist, prev, S);

    for (int i = 0; i < g.vertexCount; i++) {
      if (i == S)
        continue;

      cout << "\n---From " << S << " to " << i << "---" << endl;
      g.printPath(i, prev);
    }
  }
}

// int main() {
//   long A, B;
//   cin >> A;
//   cin >> B;
//
//   graph g;
//   g.init(A);
//
//   for (int i = 0; i < B; i++) {
//     long v1, v2, w;
//     cin >> v1;
//     cin >> v2;
//     cin >> w;
//
//     g.add_edge(v1 - 1, v2 - 1, w);
//   }
//
//   vector<long> prev, result;
//   g.dijkstra(result, prev, 2);
//   g.printPath(0, prev);
//
//   return 0;
//
//   // for (int i = 0; i < N; i++) {
//   //   long S;
//   //   cin >> S;
//   //
//   //   if (S > A)
//   //     continue;
//   //
//   //   vector<long> prev, result;
//   //   g.dijkstra(prev, result, S - 1);
//   //
//   //   for (int i = 0; i < g.vertexCount; i++) {
//   //     if (i == S)
//   //       continue;
//   //     g.printPath(i, prev);
//   //   }
//   // }
// }
