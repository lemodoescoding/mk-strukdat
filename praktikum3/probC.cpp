#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <utility>
using namespace std;

struct graph {
  long vertexCount, edgeCount;
  vector<vector<pair<long, long>>> adjList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;

    adjList.clear();
    for (int i = 0; i < vertexCount; i++) {
      adjList.push_back({}); // inserts V ammount of empty vector
    }
  }

  void add_edge(long vertex1, long vertex2, long weight) {
    adjList[vertex1].push_back(make_pair(vertex2, weight));
    adjList[vertex2].push_back(make_pair(vertex1, weight));
    edgeCount++;
  }

  bool dfsRec(vector<vector<pair<long, long>>> &adj,
              set<pair<long, long>> visitedEdges, long s, long currentW,
              long target) {
    if (currentW == target)
      return true;
    if (currentW > target)
      return false;

    for (auto &[u, w] : adjList[s]) {
      pair<long, long> edge = {min(u, s), max(u, s)};

      if (visitedEdges.count(edge))
        continue;

      visitedEdges.insert(edge);

      if (dfsRec(adj, visitedEdges, u, currentW + w, target)) {
        return true;
      }

      visitedEdges.erase(edge);
    }

    return false;
  }

  void DFS(vector<long> &res, long target) {
    set<pair<long, long>> visitedEdges;

    for (int node = 0; node < vertexCount; node++) {
      visitedEdges.clear();

      long currentW = 0;
      if (dfsRec(adjList, visitedEdges, node, currentW, target)) {
        cout << "YES" << endl;
        return;
      }
    }

    cout << "NO" << endl;
  }
};

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    set<long> vertexes;

    vector<tuple<long, long, long>> edges;

    while (true) {
      long i, j, w;
      cin >> i;
      cin >> j;
      cin >> w;

      if (i == 0 && j == 0 && w == 0)
        break;

      vertexes.insert(i);
      vertexes.insert(j);

      edges.push_back({i, j, w});
    }

    long x;
    cin >> x;

    map<long, long> vertexMap;
    long idx = 0;
    for (auto v : vertexes) {
      vertexMap[v] = idx++;
    }

    long g_size = vertexes.size();

    graph g;
    g.init(g_size);

    for (auto &[i, j, w] : edges) {
      g.add_edge(vertexMap[i], vertexMap[j], w);
    }

    vector<long> res(g.vertexCount, -1), distances(g.vertexCount, -1);
    g.DFS(res, x);
  }
  return 0;
}
