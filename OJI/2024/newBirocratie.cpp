
#include <bits/stdc++.h>
using namespace std;

ifstream fin("birocratie.in");
ofstream fout("birocratie.out");

const long long NEG_INF = -1e18;

int n;
vector<vector<long long>> mat, dp;

bool inBounds(int x, int y) { return x >= 0 && y >= 0 && x < n && y < n; }

int main() {
  fin >> n;
  mat.assign(n, vector<long long>(n));
  dp.assign(n, vector<long long>(n, NEG_INF));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      fin >> mat[i][j];
  for (int d = 0; d <= 2 * (n - 1); d++) {
    for (int i = 0; i < n; i++) {
      int j = d - i;
      if (!inBounds(i, j))
        continue;

      if (i == 0 && j == 0) {
        dp[i][j] = mat[i][j];
        continue;
      }

      long long best = NEG_INF;

      if (inBounds(i - 1, j))
        best = max(best, dp[i - 1][j]);
      if (inBounds(i, j - 1))
        best = max(best, dp[i][j - 1]);
      if (inBounds(i - 1, j + 1))
        best = max(best, dp[i - 1][j + 1]);
      if (inBounds(i + 1, j - 1))
        best = max(best, dp[i + 1][j - 1]);

      dp[i][j] = best + mat[i][j];
    }
  }

  fout << dp[n - 1][n - 1];
  return 0;
}
