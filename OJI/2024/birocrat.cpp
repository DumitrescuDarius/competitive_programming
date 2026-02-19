#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("birocratie.in");
ofstream fout("birocratie.out");
vector<vector<int>> mat, dp;
const int inf = 1e9 + 7;
int n;

bool inBounds(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < n)
    return 1;
  return 0;
}

int leftUp(int x, int y) {
  int left = -inf, up = -inf, upR = -inf;
  if (inBounds(x, y - 1))
    left = dp[x][y - 1];
  if (inBounds(x - 1, y))
    up = dp[x - 1][y];
  if (inBounds(x - 1, y + 1))
    upR = dp[x - 1][y + 1];
  left = max(left, upR);

  return max(left, up) + mat[x][y];
}

int bestDiag(int x, int y) {
  int newX = x - 1;
  int newY = y - 1;
  int maxDp = -inf, sum = 0;

  while (inBounds(newX, newY)) {
    maxDp = max(maxDp, sum + dp[newX][newY]);
    sum += mat[newX][newY];
    newX++;
    newY--;
  }
  newX = x - 1;
  newY = y - 1;
  sum = 0;

  while (inBounds(newX, newY)) {
    maxDp = max(maxDp, sum + dp[newX][newY]);
    sum += mat[newX][newY];
    newX--;
    newY++;
  }
  return maxDp + mat[x][y];
}

int main() {
  fin >> n;
  mat.resize(n, vector<int>(n));
  dp.resize(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      fin >> mat[i][j];

  dp[0][0] = mat[0][0];
  for (int i = 1; i < 2 * n; i++) {
    int px = 0, py = i;

    while (py >= 0) {
      if (inBounds(px, py)) {
        dp[px][py] = bestDiag(px, py);
      }
      px++;
      py--;
    }
    px = 0;
    py = i;
    while (py >= 0) {
      if (inBounds(px, py)) {
        dp[px][py] = max(dp[px][py], leftUp(px, py));
      }
      px++;
      py--;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << dp[i][j] << " ";
    cout << "\n";
  }
  fout << dp[n - 1][n - 1];
  return 0;
}
