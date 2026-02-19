#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("joc.in");
ofstream fout("joc.out");
signed main() {
  int n, m;
  fin >> n >> m;
  vector<vector<int>> dp(2, vector<int>(n, 0));
  vector<vector<int>> matrix(2, vector<int>(n, 0));

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < n; j++)
      fin >> matrix[i][j];
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < 2; i++) {
      if (j == 0) {
        dp[i][j] = matrix[i][j];
        continue;
      }
      int sum = 0;
      dp[i][j] = INT_MIN;
      for (int k = j - 1; k >= max(j - m + 1, 0LL); k--) {
        sum += dp[i ^ 1][k];
        sum += matrix[i][k];
        dp[i][j] = max(dp[i][j], sum);
        sum -= dp[i ^ 1][k];
      }
    }
    if (j == 0) {
      dp[1][j] += dp[0][j];
      cout << dp[0][j] << " ";
      continue;
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
