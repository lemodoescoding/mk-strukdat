#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
  int n, m;
  cin >> n;
  cin >> m;

  vector<vector<bool>> graph(n, vector<bool>(n, false));

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a;
    cin >> b;

    graph[--a][--b] = true;
  }

  vector<vector<long long>> dp(n, vector<long long>(1 << n, 0));
  dp[0][1] = 1; // start at city 0 (1 in 1-based index), only city 0 is visited

  for (int mask = 1; mask < (1 << n); ++mask) {
    for (int u = 0; u < n; ++u) {
      if (!(mask & (1 << u)))
        continue; // u is not visited
      if (dp[u][mask] == 0)
        continue;

      // Try to go from u to v
      for (int v = 0; v < n; ++v) {
        if (graph[u][v] && !(mask & (1 << v))) {
          int new_mask = mask | (1 << v);
          dp[v][new_mask] = (dp[v][new_mask] + dp[u][mask]) % MOD;
        }
      }
    }
  }

  // The answer is number of ways to reach city n-1 (city n in 1-based) with all
  // cities visited
  cout << dp[n - 1][(1 << n) - 1] << endl;
  return 0;

  // int dp[n][(1 << n)];
  //
  // memset(dp, 0, sizeof dp);
  // dp[0][1] = 1;
  //
  // for (int i = 2; i < (1 << n); ++i) {
  //   if ((i & (1 << 0)) == 0)
  //     continue;
  //
  //   if ((i & (i << (n - 1))) && i != ((1 << n) - 1))
  //     continue;
  //
  //   for (int j = 0; j < n; ++j) {
  //     if ((i & (1 << j)) == 0)
  //       continue;
  //
  //     int prev = i - (1 << j);
  //
  //     for (int it : graph[j]) {
  //       if ((i & (1 << it))) {
  //         dp[j][i] += dp[it][prev];
  //       }
  //     }
  //   }
  // }
  //
  // cout << dp[n - 1][(1 << n) - 1] << endl;
}
