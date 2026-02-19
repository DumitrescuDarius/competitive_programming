#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
ifstream fin("pestelee.in");
ofstream fout("pestelee.out");
vector<vector<int>> matrix;
vector<vector<int>> path;
vector<vector<int>> revPath;
const int MOD = 10007;
int n, m;

vector<pair<int, int>> delta = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

bool inBounds(int x, int y) {
  if (x >= 1 && x <= n && y >= 1 && y <= m)
    return 1;
  return 0;
}

void lee(int x, int y) {
  queue<pair<int, int>> q;
  q.push({x, y});
  path[x][y] = 1;
  while (!q.empty()) {
    pair<int, int> curr = q.front();
    q.pop();
    for (auto it : delta) {
      int dx = curr.first + it.first;
      int dy = curr.second + it.second;
      if (inBounds(dx, dy) && path[dx][dy] == 0) {
        path[dx][dy] = path[curr.first][curr.second] + 1;
        if (matrix[dx][dy] == 0)
          q.push({dx, dy});
      }
    }
  }
}

void revLee(int x, int y) {
  queue<pair<int, int>> q;
  q.push({x, y});
  revPath[x][y] = 1;
  while (!q.empty()) {
    pair<int, int> curr = q.front();
    q.pop();
    for (auto it : delta) {
      int dx = curr.first + it.first;
      int dy = curr.second + it.second;
      if (inBounds(dx, dy) &&
          path[curr.first][curr.second] - 1 == path[dx][dy] &&
          matrix[dx][dy] == 0) {
        if (revPath[dx][dy] == 0)
          q.push({dx, dy});
        revPath[dx][dy] =
            (revPath[dx][dy] + revPath[curr.first][curr.second]) % MOD;
      }
    }
  }
}

int main() {
  fin >> n >> m;
  matrix.resize(n + 1, vector<int>(m + 1, 0));
  path.resize(n + 1, vector<int>(m + 1, 0));
  revPath.resize(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      fin >> matrix[i][j];
    }
  }
  int x1, y1, x2, y2, cases;
  fin >> x1 >> y1 >> x2 >> y2;
  fin >> cases;

  lee(x1, y1);
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= m; j++) {
  //     cout << path[i][j] << " ";
  //   }
  //   cout << "\n";
  // }

  if (cases == 1) {
    fout << path[x2][y2];
  }
  if (cases == 2) {
    revLee(x2, y2);

    fout << revPath[x1][y1];
  }
}
