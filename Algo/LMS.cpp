
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int largestMagicSquare(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // prefix sums
    vector<vector<long long>> row(n, vector<long long>(m + 1, 0));
    vector<vector<long long>> col(n + 1, vector<long long>(m, 0));
    vector<vector<long long>> diag1(n + 1, vector<long long>(m + 1, 0));
    vector<vector<long long>> diag2(n + 1, vector<long long>(m + 1, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        row[i][j + 1] = row[i][j] + grid[i][j];
        col[i + 1][j] = col[i][j] + grid[i][j];
        diag1[i + 1][j + 1] = diag1[i][j] + grid[i][j];
        diag2[i + 1][j] = diag2[i][j + 1] + grid[i][j];
      }
    }

    for (int k = min(n, m); k >= 2; k--) {
      for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j + k <= m; j++) {

          long long target = row[i][j + k] - row[i][j];

          bool ok = true;

          // check rows
          for (int r = i; r < i + k; r++) {
            if (row[r][j + k] - row[r][j] != target) {
              ok = false;
              break;
            }
          }

          // check columns
          for (int c = j; c < j + k && ok; c++) {
            if (col[i + k][c] - col[i][c] != target) {
              ok = false;
              break;
            }
          }

          // diagonals
          long long d1 = diag1[i + k][j + k] - diag1[i][j];
          long long d2 = diag2[i + k][j] - diag2[i][j + k];

          if (d1 != target || d2 != target)
            ok = false;

          if (ok)
            return k;
        }
      }
    }

    return 1;
  }
};
