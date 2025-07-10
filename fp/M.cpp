#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  long N;
  cin >> N;

  map<string, long> stocks;

  for (int i = 0; i < N; i++) {
    string cmd, fruit_name;
    long qty;

    cin >> cmd;
    cin >> fruit_name;
    cin >> qty;

    if (cmd == "ADD") {
      if (stocks.count(fruit_name)) {
        stocks[fruit_name] += qty;
        continue;
      }
      stocks.insert({fruit_name, qty});

    } else if (cmd == "SELL") {
      if (!stocks.count(fruit_name)) {
        cout << "item not found" << endl;
        continue;
      }

      if (stocks.count(fruit_name) && stocks[fruit_name] < qty) {
        cout << "not enough stock" << endl;
        continue;
      }

      if (stocks.count(fruit_name) && stocks[fruit_name] >= qty) {
        stocks[fruit_name] -= qty;
        cout << "SUCCESS" << endl;
        continue;
      }
    }
  }
}
