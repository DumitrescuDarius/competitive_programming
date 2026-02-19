#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("turcane.in");
ofstream fout("turcane.out");
const int MOD = 1e9 + 7;
int n, m;

vector<pair<int, int>> delta = {{0, -1}, {-1, 0}, {-1, -1}, {-2, -1}, {-1, -2}};

vector<vector<int>> dp;
vector<vector<int>> seen;

bool inBounds(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < m)
    return 1;
  return 0;
}

int cntPath(int x, int y, int q, int type) {
  int ans = 0;
  x += delta[type].first;
  y += delta[type].second;
  if (!inBounds(x, y))
    return 0;
  ans = dp[x][y] * 2;
  x += delta[type].first * q;
  y += delta[type].second * q;
  if (inBounds(x, y))
    ans -= dp[x][y];
  return ans;
}

int cntHorse(int x, int y, int type) {
  x += delta[type].first;
  y += delta[type].second;
  if (inBounds(x, y))
    return dp[x][y];
  return 0;
}

int main() {
  int cases, p, q, r;
  vector<int> mult(5);
  fin >> cases;
  fin >> n >> m;
  fin >> p >> q >> r;
  mult = {p, q, r, 1, 1};
  if (cases == 1) {
    seen.assign(n, vector<int>(m, 0));
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
      pair<int, int> cell = q.front();
      q.pop();
      for (auto it : delta) {
        int dx = cell.first;
        int dy = cell.second;
        int mIndex = 0;
        for (int i = 0; i < mult[mIndex]; i++) {
          dx += (it.first * -1);
          dy += (it.second * -1);
          if (!inBounds(dx, dy) || seen[dx][dy] != 0)
            break;
          seen[dx][dy] = seen[cell.first][cell.second] + 1;
          q.push({dx, dy});
        }
        mIndex++;
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << seen[i][j] << " ";
      }
      cout << "\n";
    }
    fout << seen[n - 1][m - 1];
  }
  if (cases == 2) {
    dp.assign(n, vector<int>(m, MOD));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (i == 0 && j == 0)
          continue;
        int cnt = cntPath(i, j, p, 0);
        cnt = (cnt + cntPath(i, j, r, 1)) % MOD;
        cnt = (cnt + cntPath(i, j, q, 2)) % MOD;
        cnt = (cnt + cntHorse(i, j, 3)) % MOD;
        cnt = (cnt + cntHorse(i, j, 4)) % MOD;

        dp[i][j] = cnt;
        cout << dp[i][j] << " ";
      }
      cout << "\n";
    }
    fout << dp[n - 1][m - 1];
  }
  return 0;
}
