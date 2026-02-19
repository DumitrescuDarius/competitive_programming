#include <bits/stdc++.h>
#include <vector>
#define nInf 1e9
using namespace std;
class Solution {
private:
  vector<vector<int>> dp;
  int traverse(int i, int j, vector<int> &nums1, vector<int> &nums2) {
    if (i == nums1.size() || j == nums2.size())
      return nInf;
    if (dp[i][j] != nInf)
      return dp[i][j];
    int take = nums1[i] * nums2[j];
    int res = max({take + traverse(i + 1, j + 1, nums1, nums2), take,
                   traverse(i + 1, j, nums1, nums2),
                   traverse(i, j + 1, nums1, nums2)});
    return dp[i][j] = res;
  }

public:
  int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
    dp.assign(nums1.size(), vector<int>(nums2.size(), nInf));
    return traverse(0, 0, nums1, nums2);
  }
};
