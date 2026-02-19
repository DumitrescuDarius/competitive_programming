#include <bits/stdc++.h>
#include <vector>
#define int long long
using namespace std;
ifstream fin("experimente.in");
ofstream fout("experimente.out");

signed main() {
  int n, m, ans = 0;
  fin >> n >> m;
  vector<pair<int, int>> intervals;
  intervals.push_back({0, n - 1});
  for (int i = 0; i < m; i++) {
    int left, right;
    fin >> left >> right;
    left = (left + ans) % n;
    right = (right + ans) % n;
    ans = 0;
    vector<pair<int, int>> newIntervals;
    for (auto it : intervals) {
      if (left <= right) {
        int newLeft = max(it.first, left);
        int newRight = min(it.second, right);
        if (newLeft <= newRight)
          newIntervals.push_back({newLeft, newRight});
      }
      if (left > right) {
        int L1 = max(it.first, left);
        int R1 = min(it.second, n - 1);
        if (L1 <= R1)
          newIntervals.push_back({L1, R1});

        int L2 = max(it.first, 0LL);
        int R2 = min(it.second, right);
        if (L2 <= R2)
          newIntervals.push_back({L2, R2});
      }
    }
    for (auto it : newIntervals)
      ans += it.second - it.first + 1;
    intervals.assign(newIntervals.begin(), newIntervals.end());
    fout << ans << "\n";
  }
}
