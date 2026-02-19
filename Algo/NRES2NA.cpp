#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  ll repeatedNTimes(vector<ll> &nums) {
    ll k;
    map<ll, ll> mp;
    for (auto it : nums) {
      mp[it]++;
      if (mp[it] == nums.size() / 2)
        k = it;
    }
    return k;
  }
};
