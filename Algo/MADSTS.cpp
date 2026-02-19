#include <bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
  int minimumDeleteSum(string s1, string s2) {
    s1.insert(s1.begin(), 0);
    s2.insert(s2.begin(), 0);
    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));
    int sum = accumulate(s1.begin(), s1.end(), 0);
    sum += accumulate(s2.begin(), s2.end(), 0);

    for (int i = 1; i < s1.size(); i++) {
      for (int j = 1; j < s2.size(); j++) {
        if (s1[i] == s2[j])
          dp[i][j] = dp[i - 1][j - 1] + s1[i];
        else
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
    return sum - dp.back().back() * 2;
  }
};
