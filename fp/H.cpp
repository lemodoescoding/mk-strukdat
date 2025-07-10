#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<long> char_count(26, 0);

  string S;

  cin >> S;

  for (int i = 0; i < S.size(); i++) {
    char_count[S[i] - 'a']++;
  }

  for (int i = 0; i < S.size(); i++) {
    if (char_count[(S[i] - 'a')] == 1) {
      cout << i << endl;
      return 0;
    }
  }

  cout << -1 << endl;
  return 0;
}
