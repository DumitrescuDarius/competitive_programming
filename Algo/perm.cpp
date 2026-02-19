#include <bits/stdc++.h>
#include <vector>
#define int long long
using namespace std;
signed main() {
  int n;
  cin >> n;
  vector<int> dp(1 << n, 0);
  dp[0] = 1;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
      if (!(mask & (1 << i)))
        dp[mask | (1 << i)] += dp[mask];
    }
  }
  cout << dp[(1 << n) - 1];
  return 0;
}
