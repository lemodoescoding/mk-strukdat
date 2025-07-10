#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

struct graph {
  long vertexCount, edgeCount;
  vector<vector<tuple<long, long, long>>> adjList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;

    for (int i = 0; i < vertexCount; i++) {
      adjList.push_back({}); // inserts V ammount of empty vector
    }
  }

  void add_edge(long vertex1, long vertex2, long weight, long isRisky) {
    adjList[vertex1].push_back({vertex2, weight, isRisky});
    adjList[vertex2].push_back({vertex1, weight, isRisky});
    edgeCount++;
  }

  void dijkstra(vector<long> &result, long start, long finish, long maxWeight) {
    vector<bool> visited(vertexCount, false);
    vector<bool> usedRisky(vertexCount, false);
    priority_queue<tuple<long, long, long>, vector<tuple<long, long, long>>,
                   greater<>>
        pq;
    result = vector<long>(vertexCount, LONG_MAX);

    long weight_start = -1;
    for (auto &[to, weight, isRisky] : adjList[start]) {
      if (isRisky == 0) {
        weight_start = weight;
        break;
      }
    }

    pq.push({0, start, -1});
    result[start] = 0;

    while (!pq.empty()) {
      auto [par, u, prev_weight] = pq.top();
      pq.pop();

      if (visited[u])
        continue;

      visited[u] = true;

      for (auto &[nextVertex, weight, isRisky] : adjList[u]) {
        if (!visited[nextVertex]) {
          long real_weight = weight;

          if (isRisky == 1) {
            if (prev_weight == -1)
              continue;

            real_weight = prev_weight + weight_start;
          }

          if (result[u] + real_weight < result[nextVertex]) {
            result[nextVertex] = result[u] + real_weight;
            usedRisky[nextVertex] = usedRisky[u] || (isRisky == 1);
            pq.push({result[nextVertex], nextVertex, real_weight});
          }
        }
      }
    }

    if (result[finish] > maxWeight) {
      cout << "Increase lift and coast please max, just try to stay in front "
              "of Lando"
           << endl;
    }

    if (usedRisky[finish] == 1 && result[finish] <= maxWeight) {
      cout << "Press to overtake and dive bomb please max" << endl;
    } else {
      cout << "Decrease lift and coast please max, oscar is slower in front of "
              "you"
           << endl;
    }
  }
};

int main() {
  int n_vertices, n_Edges;

  cin >> n_vertices;
  cin >> n_Edges;

  graph g;
  g.init(n_vertices);

  for (int i = 0; i < n_Edges; i++) {
    int vertex1, vertex2, weight, isRisky;

    cin >> vertex1;
    cin >> vertex2;
    cin >> weight;
    cin >> isRisky;

    g.add_edge(vertex1, vertex2, weight, isRisky);
  }

  long start_node, finish_node, maxWeight;
  cin >> start_node;
  cin >> finish_node;
  cin >> maxWeight;

  vector<long> result, prev;
  g.dijkstra(result, start_node, finish_node, maxWeight);

  return 0;
}
