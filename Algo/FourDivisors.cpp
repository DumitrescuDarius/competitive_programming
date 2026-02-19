#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  ll sumFourDivisors(vector<ll> &nums) {
    ll ans = 0;
    for (auto it : nums) {
      ll cont = 0, sum = 0, x = it, i;
      for (i = 1; i * i < x; i++) {
        if (x % i == 0) {
          cont += 2;
          sum += i + x / i;
        }
      }
      if (i * i == x) {
        cont++;
        sum += i;
      }
      if (cont == 4)
        ans += sum;
    }
    return ans;
  }
};
