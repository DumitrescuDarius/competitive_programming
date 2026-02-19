#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("gradina.in");
ofstream fout("gradina.out");
const int MOD = 1e9 + 7;
signed main() {
  int k, n;
  fin >> k >> n;
  int ans = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    vector<int> allowed;

    for (int i = 0; i < n; i++) {
      if (!(mask & (1 << i)))
        allowed.push_back(i);

      vector<int> dp(k + 1, 0);

      dp[0] = 1;

      for (int i = 1; i <= k; i++) {
        for (int len : allowed)
          if (i - len >= 0)
            dp[i] = (dp[i] + dp[i - len]) % MOD;
      }

      if ()
    }
  }
}
