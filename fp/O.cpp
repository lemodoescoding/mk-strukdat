#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool isValidPreorder(vector<long> &nodes) {
  stack<long> st;

  long root = LONG_MIN;

  for (int i = 0; i < nodes.size(); i++) {
    if (nodes[i] < root)
      return false;

    while (!st.empty() && st.top() < nodes[i]) {
      root = st.top();
      st.pop();
    }

    st.push(nodes[i]);
  }

  return true;
}

int main() {
  long N;
  cin >> N;

  vector<long> nodes(N);
  for (int i = 0; i < N; i++) {
    long A = 0;
    cin >> A;

    nodes.push_back(A);
  }

  bool res = isValidPreorder(nodes);

  if (res)
    cout << "Ini pohon" << endl;
  else
    cout << "Ini bukan pohon" << endl;
}
