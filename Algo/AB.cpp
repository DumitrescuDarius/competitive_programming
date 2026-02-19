#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  string addBinary(string a, string b) {
    string sum = a;
    int k = b.size() - 1;
    int remain = 0;
    for (int i = sum.size() - 1; i >= 0; i--) {
      if (remain) {
        sum[i] = '1' * (sum[i] == '0') + '0' * (sum[i] == '1');
        if (sum[i] == 0)
          remain = 1;
      }
      if (sum[i] != b[k])
        sum[i] = '1';
      else if (sum[i] == '1')
        remain = 0;
      k--;
    }
    return sum;
  }
};
