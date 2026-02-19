#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int MOD = 123457;
int main() {
  int n;
  cin >> n;
  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int d = 1; d <= n; d++) {
    if (n % d == 0)
      for (int i = d; i <= n; i++)
        dp[i] = (dp[i] + dp[i - d]) % MOD;
  }
  cout << dp[n];
}
