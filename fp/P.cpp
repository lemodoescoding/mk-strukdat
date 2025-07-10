#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

int main() {
  int p, q;
  cin >> p;
  cin >> q;

  vector<char> task(p);
  for (int i = 0; i < p; i++)
    cin >> task[i];

  map<char, int> frequency;
  map<char, int> cooldown;

  for (char t : task) {
    frequency[t]++;
  }

  queue<char> taskQueue;

  for (char c : task) {
    if (frequency[c] > 0)
      taskQueue.push(c);
  }

  int time = 0;
  int rest = p;

  while (rest > 0) {
    time++;

    for (int i = 0; i < taskQueue.size(); i++) {
      char taskNow = taskQueue.front();

      taskQueue.pop();

      if (frequency[taskNow] > 0 && cooldown[taskNow] <= time) {
        frequency[taskNow]--;
        cooldown[taskNow] = time + q + 1;
        rest--;

        taskQueue.push(taskNow);
        break;
      }

      taskQueue.push(taskNow);
    }
  }

  cout << time << endl;
  return 0;
}
