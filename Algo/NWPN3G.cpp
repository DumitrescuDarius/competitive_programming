#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
  ll numOfWays(ll n) {
    const ll MOD = 10e9 + 7;
    vector<vector<ll>> dp(n + 1, vector<ll>(3, 0));
    dp[1][0] = 1;
    dp[1][1] = 1;
    dp[1][2] = 1;
    for (ll i = 1; i <= n; i++) {
    }
  }
};
