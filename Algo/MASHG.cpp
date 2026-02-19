#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int maximizeSquareHoleArea(int n, int m, vector<int> &hBars,
                             vector<int> &vBars) {
    sort(hBars.begin(), hBars.end());
    sort(vBars.begin(), vBars.end());
    int cnt = 1;
    int hMax = 1;
    for (int i = 1; i < hBars.size(); i++) {
      if (hBars[i - 1] + 1 == hBars[i])
        cnt++;
      else
        cnt = 1;
      hMax = max(hMax, cnt);
    }
    cnt = 1;
    int vMax = 1;
    for (int i = 1; i < vBars.size(); i++) {
      if (vBars[i - 1] + 1 == vBars[i])
        cnt++;
      else
        cnt = 1;
      vMax = max(vMax, cnt);
    }
    int side = min(hMax, vMax) + 1;
    int ans = side * side;
    return ans;
  }
};
