#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
  double champagneTower(int poured, int query_row, int query_glass) {
    vector<vector<double>> dp(100, vector<double>(100, 0));
    dp[0][1] = poured;
    for (int i = 1; i < 100; i++) {
      for (int j = 1; j < 100; j++) {
        if (dp[i - 1][j - 1] > 1)
          dp[i][j] += dp[i - 1][j - 1] - 1;
        if (dp[i - 1][j] > 1)
          dp[i][j] += dp[i - 1][j] - 1;
      }
    }
    return dp[query_row][query_glass + 1];
  }
};
