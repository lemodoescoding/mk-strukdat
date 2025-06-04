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
    cout << " " << end;
  }
};

int main() {
  int V, N;
  cin >> V;
  cin >> N;

  graph g;

  g.init(V);

  for (int i = 0; i < N; i++) {
    int src, dest, weight;
    cin >> src;
    cin >> dest;
    cin >> weight;

    g.add_edge(src, dest, weight);
  }

  int S, E;

  cin >> S;
  cin >> E;

  vector<long> dist, prev;
  g.dijkstra(dist, prev, S);

  // for (int i = 0; i < dist.size(); i++) {
  //   cout << i << " " << dist[i] << endl;
  // }

  if (dist[E] == LONG_MAX) {
    cout << "Impossible to find the path" << endl;
  } else {
    cout << "Path found with cost " << dist[E] << ": ";
    g.printPath(E, prev);
  }
}
