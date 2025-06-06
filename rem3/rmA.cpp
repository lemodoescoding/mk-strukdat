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
  vector<pair<long, pair<long, long>>> edgeList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;

    for (int i = 0; i < vertexCount; i++) {
      adjList.push_back({});
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

  void kruskal(vector<pair<long, pair<long, long>>> &result, long budget) {
    vector<long> parent;
    for (int i = 0; i < vertexCount; i++)
      parent.push_back(i);

    long budget_temp = budget;

    sort(edgeList.begin(), edgeList.end());

    for (auto edge : edgeList) {
      long vertex1 = edge.second.first;
      long vertex2 = edge.second.second;
      if (find_parent(parent, vertex1) != find_parent(parent, vertex2)) {
        result.push_back(edge);
        union_set(parent, vertex1, vertex2);

        budget_temp -= edge.first;

        if (result.size() == vertexCount - 1) {

          if (budget_temp >= 0) {
            cout << "Budgetnya cukup Bos! Ada sisa " << budget_temp << endl;
          } else {
            cout << "Waduh budgetnya kurang bos" << endl;
          }
          return;
        }
      }
    }
  }
};

int main() {
  long v, e;
  cin >> v;
  cin >> e;

  graph g;
  g.init(v);

  for (int i = 0; i < e; i++) {
    long a, b, w;

    cin >> a;
    cin >> b;
    cin >> w;

    g.add_edge(a - 1, b - 1, w);
  }

  long p;
  cin >> p;
  vector<pair<long, pair<long, long>>> result;

  g.kruskal(result, p);
}
