#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N, M;
  cin >> N;
  cin >> M;

  vector<bool> orderStatus(N + 2, false);
  orderStatus[0] = orderStatus[N + 1] = true;

  for (int i = 0; i < M; i++) {
    int A;
    cin >> A;

    orderStatus[A] = !orderStatus[A];

    int K = 0;

    for (int i = 1; i < N + 1; i++) {
      if (orderStatus[i] == true)
        continue;

      // cout << "i: " << i << endl;

      int left = i, right = i;

      while (!orderStatus[right] && right <= N + 1) {
        right++;
      }

      // cout << "Right: " << right << endl;

      while (!orderStatus[left] && left >= 0) {
        left--;
      }

      // cout << "Left: " << left << endl;

      K += abs(i - right) * abs(i - left);
    }

    cout << K << endl;
  }
}
