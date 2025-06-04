#include <climits>
#include <iostream>
#include <queue>
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
}
