#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("gradina.in");
ofstream fout("gradina.out");
const int MOD = 1e9 + 7;
signed main() {
  int n, t;
  fin >> n >> t;

  vector<vector<int>> dp((1 << t), vector<int>(n + 1, 0));

  dp[0][0] = 1;
  for (int mask = 0; mask < (1 << t); mask++) {
    for (int j = 0; j <= n; j++) {
      if (!dp[mask][j])
        continue;
      for (int i = 1; i <= t; i++) {
        if (j + i > n)
          continue;
        int newMask = mask | (1 << (i - 1));
        dp[newMask][j + i] = (dp[newMask][j + i] + dp[mask][j]) % MOD;
      }
    }
  }

  fout << dp[(1 << t) - 1][n];
}
