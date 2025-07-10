#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>
using namespace std;

struct graph {
  long vertexCount, edgeCount;
  vector<vector<pair<long, long>>> adjList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;

    for (long i = 0; i < vertexCount; i++) {
      adjList.push_back({});
    }
  }

  void add_edge(long vertex1, long vertex2, long weight) {
    adjList[vertex1].push_back(make_pair(vertex2, weight));
    adjList[vertex2].push_back(make_pair(vertex1, weight));
    edgeCount++;
  }

  void dijkstra(long N, long start, long end) {
    priority_queue<tuple<long, long, long>, vector<tuple<long, long, long>>,
                   greater<>>
        pq;
    vector<vector<long>> dist(N, vector<long>(2, LONG_MAX));
    vector<vector<long>> node_count(N, vector<long>(2, 0));

    dist[start][0] = 0;
    node_count[start][0] = 1;

    pq.emplace(0, start, 0);

    while (!pq.empty()) {
      auto [cur_cst, par, c_used] = pq.top();
      pq.pop();

      if (cur_cst > dist[par][c_used])
        continue;

      for (auto neighbour : adjList[par]) {
        long v = neighbour.first;
        long w = neighbour.second;

        if (dist[v][c_used] > cur_cst + w) {
          dist[v][c_used] = cur_cst + w;
          node_count[v][c_used] = node_count[par][c_used] + 1;
          pq.emplace(dist[v][c_used], v, c_used);
        }

        if (c_used == 0 && node_count[par][0] + 1 >= ((N) / 2)) {
          long reduced = cur_cst + (w / 2);

          if (dist[v][1] > reduced) {
            dist[v][1] = reduced;

            node_count[v][1] = node_count[par][0] + 1;
            pq.emplace(reduced, v, 1);
          }
        }
      }
    }

    cout << min(dist[end][0], dist[end][1]) << endl;
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

  for (long i = 0; i < M; i++) {
    long a, b, c;

    cin >> a;
    cin >> b;
    cin >> c;

    g.add_edge(--a, --b, c);
  }

  g.dijkstra(N, --S, --T);
}
