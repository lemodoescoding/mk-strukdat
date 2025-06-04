#include <bits/stdc++.h>
#include <set>
using namespace std;

int main() {
  set<int> s;

  s.insert(4);
  s.insert(3);
  s.insert(2);
  s.insert(1);
  s.insert(1);

  for (auto i = s.begin(); i != s.end(); i++) {
    cout << *i << endl;
  }

  return 0;
}
