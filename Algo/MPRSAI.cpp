#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
private:
  bool isSorted(vector<int> &nums) {
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i - 1] > nums[i]) {
        // cout << nums[i - 1] << " " << nums[i] << "\n";
        return 0;
      }
    }
    return 1;
  }

public:
  int minimumPairRemoval(vector<int> &nums) {
    int ans = 0;
    while (isSorted(nums) == 0 && nums.size() > 1) {
      int maxVal = INT_MAX;
      int pos = -1;
      ans++;
      for (int i = 1; i < nums.size(); i++) {
        if (maxVal < nums[i] + nums[i - 1]) {
          maxVal = nums[i] + nums[i - 1];
          pos = i;
        }
      }
      for (auto it : nums)
        cout << it << " ";
      cout << "\n";
      cout << pos << " ";
      if (pos > 0) {
        nums.erase(nums.begin() + pos);
        nums[pos - 1] = maxVal;
      }
    }
    return ans;
  }
};
