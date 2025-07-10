#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

struct DSU {
  map<string, string> parent;
  set<string> unique_roots;

  string find(string x) {
    if (parent.find(x) == parent.end())
      parent[x] = x;
    if (parent[x] != x)
      parent[x] = find(parent[x]);

    return parent[x];
  }

  void union_set(string friend1, string friend2) {
    friend1 = find(friend1);
    friend2 = find(friend2);

    if (friend1 != friend2)
      parent[friend2] = friend1;
  }

  long countRoots() {
    for (auto &p : parent) {
      unique_roots.insert(find(p.first));
    }

    return unique_roots.size();
  }

  long totalNodes() { return parent.size(); }
};

int main() {
  long N, M;
  cin >> N;
  cin >> M;

  DSU dsu;

  for (int i = 0; i < M; i++) {
    string friend1, friend2;

    cin >> friend1;
    cin >> friend2;
    dsu.union_set(friend1, friend2);
  }

  long energy;
  cin >> energy;

  long uniq_parents = dsu.countRoots();

  long total_components = uniq_parents + 2;
  long minimumEnergy = total_components - 2 + 1;

  if (energy >= minimumEnergy) {
    cout << "You tied the loose ends and reached her." << endl;
  } else if (energy >= (total_components - 2)) {
    cout << "You tied the loose ends but couldn\'t reach her." << endl;
  } else {
    cout << "You didn\'t tie the loose ends. She remains out of reach." << endl;
  }
}
