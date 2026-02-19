#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  vector<ll> plusOne(vector<ll> &digits) {
    digits[digits.size() - 1]++;
    for (ll i = digits.size() - 1; i >= 0; i--) {
      if (digits[i] == 10) {
        digits[i] = 0;
        if (i > 0)
          digits[i - 1]++;
        else
          digits.insert(digits.begin(), 1);
      }
    }
    return digits;
  }
};
