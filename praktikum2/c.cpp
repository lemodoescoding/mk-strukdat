#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

bool mapcmp(pair<int, int> &a, pair<int, int> &b) { return a.first - a.second; }

int main() {
  int n = 0, X = 0;

  cin >> n;
  cin >> X;

  map<int, int> districts;

  for (int i = 0; i < X; i++) {
    int c;
    cin >> c;

    districts[c]++;
  }

  int mid_dist = (X % 2 == 0) ? (X / 2) : (int)floor(X / 2) + 1;

  int greatest_dist = 0, curr_val = 0;
  for (auto i = districts.begin(); i != districts.end(); i++) {
    if (i->second > curr_val) {
      curr_val = i->second;
      greatest_dist = i->first;
    }
  }

  cout << greatest_dist << " ";

  int mid_dist_real = 1;

  int i_temp = 1;
  bool finish = false;
  for (auto i = districts.begin(); i != districts.end(); i++) {
    if (i->second == 1 && i_temp < mid_dist) {
      // cout << "yes " << i_temp << endl;
      i_temp++;

      continue;
    } else if (i->second > 1 && i_temp < mid_dist) {
      for (int j = 0; j < i->second; j++) {
        if (i_temp < mid_dist) {
          // cout << "yes " << j << " " << i_temp << endl;
          i_temp++;
        } else if (i_temp == mid_dist) {
          // cout << "end " << i_temp << endl;
          finish = true;
          break;
        }
      }
    } else if (i_temp == mid_dist) {
      cout << i->first << endl;
      mid_dist_real = i->first;
      break;
    }

    if (finish) {
      mid_dist_real = i->first;
      cout << i->first << endl;
      break;
    }
  }

  if (greatest_dist == mid_dist_real) {
    cout << "Tidak ada yang menang" << endl;
  } else {
    cout << "Distrik " << greatest_dist << " menang" << endl;
  }
}
