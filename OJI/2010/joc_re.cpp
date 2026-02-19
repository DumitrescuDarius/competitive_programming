#include <bits/stdc++.h>
#include <climits>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("joc.in");
ofstream fout("joc.out");
signed main() {
  int n, k;
  fin >> n >> k;
  vector<vector<int>> matrix(2, vector<int>(n, 0)),
      dp(2, vector<int>(n, INT_MIN));
  for (int i = 0; i <= 1; i++)
    for (int j = 0; j < n; j++)
      fin >> matrix[i][j];
  dp[0][0] = matrix[0][0];
  dp[1][0] = matrix[0][0] + matrix[1][0];
  cout << dp[0][0] << " ";
  for (int j = 1; j < n; j++) {
    for (int i = 0; i <= 1; i++) {
      int leftmost = max(0LL, j - k + 1);
      int sum = 0;
      for (int r = j - 1; r >= leftmost; r--) {
        sum += dp[i][r];
        dp[i][j] = max(dp[i][j], sum);
        sum -= dp[i][r];
        sum += matrix[i][r];
      }
      dp[i][j] += matrix[i][j];
    }
    int t1 = dp[0][j];
    int t2 = dp[1][j];

    dp[0][j] = max(dp[0][j], t2 + matrix[0][j]);
    dp[1][j] = max(dp[1][j], t1 + matrix[1][j]);

    cout << dp[0][j] << " ";
  }
  cout << "\n";
  for (int j = 0; j < n; j++)
    cout << dp[1][j] << " ";
  fout << dp[1][n - 1];
  return 0;
}
