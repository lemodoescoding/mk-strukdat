#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int dir_x[4] = {0, 1, 0, -1};
int dir_y[4] = {1, 0, -1, 0};

long DFS(vector<vector<char>> &board, vector<vector<bool>> &board_visited,
         long idx, long idy, long H, long W) {
  board_visited[idy][idx] = true;

  long size = 1;

  for (int i = 0; i < 4; i++) {
    long move_x = idx + dir_x[i];
    long move_y = idy + dir_y[i];

    if (move_x >= 0 && move_x < W && move_y >= 0 && move_y < H &&
        !board_visited[move_y][move_x] && board[move_y][move_x] == '+') {
      size += DFS(board, board_visited, move_x, move_y, H, W);
    }
  }

  return size;
}

int main() {
  int H, W;
  cin >> H;
  cin >> W;

  vector<vector<char>> board(H, vector<char>(W));
  vector<vector<bool>> board_visited(H, vector<bool>(W, false));

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      char cell;
      cin >> cell;

      board[i][j] = cell;
    }
  }

  long C = 0, S = 0, E = 0;

  vector<int> colonies;

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (board[i][j] == '+' && !board_visited[i][j]) {
        // board_visited[i][j] = true;

        long size = DFS(board, board_visited, j, i, H, W);
        C++;

        if (size > S)
          S = size;
        if (size % 2 == 0)
          E++;
      }
    }
  }

  cout << C << " " << S << " " << E << endl;
  return 0;
}
