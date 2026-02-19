#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("camelot.in");
ofstream fout("camelot.out");
const int inf = 1e9 + 7;
vector<vector<int>> delta = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2},
                             {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

struct cell {
  int x, y, weight, index;
};

int n, m, qx, qy;

vector<vector<int>> matrix;

bool inBounds(int x, int y) {
  if (x >= 1 && x <= n && y >= 1 && y <= m)
    return 1;
  return 0;
}

int main() {
  int cases, k;
  fin >> cases;
  fin >> n >> m >> k;
  vector<pair<int, int>> horses;
  matrix.assign(n + 1, vector<int>(m + 1, inf));
  fin >> qx >> qy;
  queue<cell> q;
  for (int i = 0; i < k; i++) {
    int x, y;
    fin >> x >> y;
    horses.push_back({x, y});
    q.push({x, y, 0, i});
    matrix[x][y] = 0;
  }

  if (cases == 1)
    while (!q.empty()) {
      cell pos = q.front();
      q.pop();
      for (auto it : delta) {
        int dx = pos.x + it[0];
        int dy = pos.y + it[1];

        if (inBounds(dx, dy) && pos.weight + 1 < matrix[dx][dy]) {
          matrix[dx][dy] = pos.weight + 1;
          q.push({dx, dy, pos.weight + 1, pos.index});
          if (dx == qx && dy == qy) {
            fout << matrix[dx][dy];
            return 0;
          }
        }
      }
    }
  else {
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, inf));
    queue<pair<int, int>> q;

    dist[qx][qy] = 0;
    q.push({qx, qy});

    while (!q.empty()) {
      pair<int, int> cur = q.front();
      q.pop();

      int x = cur.first;
      int y = cur.second;

      for (auto &d : delta) {
        int nx = x + d[0];
        int ny = y + d[1];

        if (inBounds(nx, ny) && dist[nx][ny] == inf) {
          dist[nx][ny] = dist[x][y] + 1;
          q.push({nx, ny});
        }
      }
    }

    int ans = 0;
    for (int i = 0; i < k; i++) {
      pair<int, int> c = horses[i];
      ans = max(ans, dist[c.first][c.second]);
    }

    fout << ans;
  }
  return 0;
}
