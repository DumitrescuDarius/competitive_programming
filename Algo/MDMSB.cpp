#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
  int minimumDeletions(string s) {
    int len = s.size();
    vector<int> sufA(len, 0);
    vector<int> prefB(len, 0);

    for (int i = 0; i < len; i++) {
      prefB[i] = (s[i] == 'b');
      if (i > 0)
        prefB[i] += prefB[i - 1];
    }

    for (int i = len - 1; i >= 0; i--) {
      sufA[i] = (s[i] == 'a');
      if (i < len - 1)
        sufA[i] += sufA[i + 1];
    }

    int ans = 1e9;
    for (int i = 0; i < len; i++) {
      int del = prefB[i] + sufA[i];
      ans = min(del, ans);
    }
    return ans;
  }
};
