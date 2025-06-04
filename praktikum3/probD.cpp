#include <algorithm>
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
      adjList.push_back({}); // inserts V ammount of empty vector
    }
  }

  void add_edge(long vertex1, long vertex2) {
    adjList[vertex1].push_back(vertex2);
    adjList[vertex2].push_back(vertex1);
    edgeCount++;
  }

  void dfs(vector<long> &result, long start) {
    vector<bool> visited(vertexCount, false);
    vector<long> parent(vertexCount, -1);
    stack<pair<long, long>> st;

    st.push({start, -1});

    while (!st.empty()) {
      auto [v, par] = st.top();
      st.pop();

      if (!visited[v]) {
        visited[v] = true;
        result.push_back(v);

        for (auto vertex : adjList[v]) {
          if (!visited[vertex]) {
            parent[vertex] = v;
            st.push({vertex, v});
          } else if (vertex != par) {
            cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED ";

            vector<long> cycle;
            auto temp = v;

            cycle.push_back(v);

            while (temp != vertex) {
              temp = parent[temp];
              cycle.push_back(temp);
            }

            sort(cycle.begin(), cycle.end());

            for (auto j : cycle) {
              cout << j;
              if (j != cycle.back())
                cout << " ";
              else
                cout << endl;
            }

            return;
          }
        }
      }
    }

    cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED" << endl;
    return;
  }
};

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    int V, N;
    cin >> V;
    cin >> N;

    graph g;
    g.init(V);

    for (int j = 0; j < N; j++) {
      int vi, vj;
      cin >> vi;
      cin >> vj;

      g.add_edge(vi, vj);
    }

    vector<long> result;
    g.dfs(result, 0);
  }
  return 0;
}
