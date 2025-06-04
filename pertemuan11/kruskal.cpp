#include <bits/stdc++.h>
using namespace std;

struct graph {
  long vertexCount, edgeCount;
  vector<vector<pair<long, long>>> adjList;
  vector<pair<long, pair<long, long>>> edgeList;

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

    edgeList.push_back(make_pair(weight, make_pair(vertex1, vertex2)));
    edgeCount++;
  }

  long find_parent(vector<long> &parent, long v) {
    if (v == parent[v])
      return v;

    return parent[v] = find_parent(parent, parent[v]);
  }

  void union_set(vector<long> &parent, long vertex1, long vertex2) {
    int parent1 = find_parent(parent, vertex1);
    int parent2 = find_parent(parent, vertex2);

    if (parent1 != parent2)
      parent[parent2] = parent1;
  }

  void kruskal(vector<pair<long, pair<long, long>>> &result) {
    vector<long> parent;
    for (int i = 0; i < vertexCount; i++)
      parent.push_back(i);

    sort(edgeList.begin(), edgeList.end());

    for (auto edge : edgeList) {
      long vertex1 = edge.second.first;
      long vertex2 = edge.second.second;
      if (find_parent(parent, vertex1) != find_parent(parent, vertex2)) {
        result.push_back(edge);
        union_set(parent, vertex1, vertex2);
        if (result.size() == vertexCount - 1)
          return;
      }
    }
  }
};

char printVertex(int vert) { return (char)(65 + vert); }

int main() {
  graph g;
  g.init(6);
  g.add_edge(0, 1, 4);
  g.add_edge(0, 4, 6);
  g.add_edge(0, 5, 5);
  g.add_edge(1, 2, 6);
  g.add_edge(1, 5, 4);
  g.add_edge(2, 3, 7);
  g.add_edge(2, 5, 5);
  g.add_edge(3, 5, 3);
  g.add_edge(3, 4, 4);

  vector<pair<long, pair<long, long>>> kruskal_result;

  g.kruskal(kruskal_result);

  for (auto it : kruskal_result) {
    cout << it.first << " " << printVertex(it.second.first) << " -> "
         << printVertex(it.second.second) << endl;
  }

  return 0;
}
