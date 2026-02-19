#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    int g, v;
    cin >> g >> v;
    dp[i][g] = v;
    for (int j = 0; j <= m; j++) {
      if (j - g >= 0) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - g] + v);
      }
      dp[i][j] = max(dp[i][j], dp[i - 1][j]);
    }
  }
  cout << dp[n][m];
}
