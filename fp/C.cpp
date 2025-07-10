#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int solve(vector<long> &cards) {
  int N = cards.size();

  long maxEnch = 0;

  vector<long> maxEnchLeft(N), maxEnchRight(N);

  maxEnchLeft[0] = cards[0];

  for (int i = 1; i < N; i++)
    maxEnchLeft[i] = max(maxEnchLeft[i - 1], cards[i]);

  maxEnchRight[N - 1] = cards[N - 1];
  for (int i = N - 2; i >= 0; i--)
    maxEnchRight[i] = max(maxEnchRight[i + 1], cards[i]);

  for (int i = 1; i < N - 1; i++)
    maxEnch += min(maxEnchLeft[i], maxEnchRight[i]) - cards[i];

  return maxEnch;
}

int main() {
  int N;
  cin >> N;

  vector<long> cards;

  for (int i = 0; i < N; i++) {
    long X;

    cin >> X;

    cards.push_back(X);
  }

  long res = solve(cards);

  cout << res << endl;
}
