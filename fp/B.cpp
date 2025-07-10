#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  long long N;
  cin >> N;

  vector<long long> h(N);
  vector<long long> w(N);

  for (long long i = 0; i < N; i++) {
    cin >> h[i];
  }

  for (long long i = 0; i < N; i++) {
    cin >> w[i];
  }

  h.push_back(0);
  w.push_back(0);

  vector<long long> prefixW(N + 1, 0);
  for (int i = 0; i < N; i++)
    prefixW[i + 1] = prefixW[i] + w[i];

  long long res = 0;
  stack<long long> st;

  for (long long i = 0; i <= N; i++) {
    while (!st.empty() && h[st.top()] >= h[i]) {
      long long tp = st.top();
      st.pop();

      long long height = h[tp];
      long long width = 0;

      if (!st.empty())
        width = prefixW[i] - prefixW[st.top() + 1];
      else
        width = prefixW[i];

      res = max(height * width, res);
    }

    st.push(i);
  }

  cout << res << endl;

  return 0;
}
