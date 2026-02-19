#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
private:
  vector<int> tree;
  int n;
  void update(int pos, int val) {
    while (pos <= n) {
      tree[pos] += val;
      pos += (pos & -pos);
    }
  }
  int query(int pos) {
    int ans = 0;
    while (pos >= 1) {
      ans += tree[pos];
      pos -= (pos & -pos);
    }
    return ans;
  }

public:
  int countRangeSum(vector<int> &nums, int lower, int upper) {}
};
