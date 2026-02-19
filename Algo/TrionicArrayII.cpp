#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
  const long long inf = 4e18;

public:
  long long maxSumTrionic(vector<int> &nums) {
    int n = nums.size();
    vector<long long> pref(n + 1, 0);
    vector<int> peaksAndLows;
    for (int i = 1; i <= n; i++)
      pref[i] = pref[i - 1] + nums[i - 1];
    for (int i = 0; i < n; i++) {
      if (i == 0)
        peaksAndLows.push_back(i);
      else if (i == n - 1)
        peaksAndLows.push_back(i);
      else {
        if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
          peaksAndLows.push_back(i);
        if (nums[i] < nums[i - 1] && nums[i] < nums[i + 1])
          peaksAndLows.push_back(i);
      }
    }
    long long ans = -inf;
    for (int i = 3; i < peaksAndLows.size(); i++) {
      int a = peaksAndLows[i - 3];
      int b = peaksAndLows[i - 2];
      int c = peaksAndLows[i - 1];
      int d = peaksAndLows[i];

      bool ok = (nums[a] < nums[b] && nums[b] > nums[c] && nums[c] < nums[d]) ||
                (nums[a] > nums[b] && nums[b] < nums[c] && nums[c] > nums[d]);

      if (!ok)
        continue;

      long long sum = pref[peaksAndLows[i] + 1] - pref[peaksAndLows[i - 3]];
      ans = max(ans, sum);
    }
    return ans;
  }
};
