
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("recyclebin.in");
ofstream fout("recyclebin.out");
int bits(int k) { return 1 << k; }

signed main() {
  int n, ans = INT32_MIN;
  fin >> n;
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT32_MIN));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    for (int mask = 0; mask <= i; mask++) {
      dp[i][mask] = dp[i - 1][mask] + x;
      for (int bit = 0; bits(bit) <= i; bit++) {
        if (bits(bit) & mask) {
          dp[i][mask] = max(dp[i][mask], dp[i - bits(bit)][mask - bits(bit)]);
        }
      }
      ans = max(ans, dp[i][mask]);
    }
  }
  fout << ans;
  return 0;
}

// 5 4 -2 4 -10
// 5
//
// dp[][]:
//
//    0:  1:  2:  3:  4:  5:  6:  7:  8:  9:  10:
// 1:  5   0   0   0   0   0   0   0   0   0   0
// 2:  9   5   0
// 3:  7   9   5   0
// 4:  11  13  9   5   0
// 5:  1   11  7   9   5   0   0
//
// 100
//
// dp[i][mask] = max(dp[i - 1][mask] + curr, dp[]
//
//
// 0:   if(mask == 0) dp[i][mask] = max(dp[i - 1][mask] + curr, curr);
// 1:   if(mask & bit(1)) dp[i][mask] = max(dp[i - 1][mask] + curr, dp[i -
// 1][mask - bit(1)]); 2:   if(mask & bit(2)) dp[i][mask] = max(dp[i - 1][mask]
// + curr, dp[i - 2][mask - bit(2)]);
//
//
//
// int bit(int k){
//  return 1 << k;
//}
//
// 1     1
// 2    10
// 3    11
// 4   100
// 5   101 5 = 2 ^ 0 + 2 ^ 2
// 6   110
// 7   111
//
//
//  mask curent = 1010
//  bit curent = 10
//  i = 12
//
//  dp[i][mask] = max(dp[i - bit(10)][bit(1000)])
//  newi = 10
//  newmask = 1000
//
//
// 4 5 -10 2 5 -10 8 9
//
// 4 9 -1 2 7
