#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int maximizeSquareArea(int m, int n, vector<int> &hFences,
                         vector<int> &vFences) {
    set<int> st;
    const int MOD = 1e9 + 7;
    hFences.push_back(1);
    hFences.push_back(m);
    vFences.push_back(1);
    vFences.push_back(n);

    sort(hFences.begin(), hFences.end());
    sort(vFences.begin(), vFences.end());

    for (int i = 0; i < hFences.size(); i++) {
      for (int j = i + 1; j < hFences.size(); j++) {
        st.insert(hFences[j] - hFences[i]);
      }
    }
    long long ans = -1;
    for (int i = 0; i < vFences.size(); i++) {
      for (int j = i + 1; j < vFences.size(); j++) {
        long long dist = 1LL * vFences[j] - vFences[i];
        if (st.count(dist))
          ans = max(ans, 1LL * (dist * dist) % MOD);
      }
    }
    return ans;
  }
};
