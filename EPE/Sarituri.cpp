#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("sarituri.in");
ofstream fout("sarituri.out");
signed main() {
  int n, k;
  fin >> n >> k;
  vector<int> dp;
  vector<int> v;

  int ans = 0;
  int x;
  fin >> x;
  v.push_back(x);
  dp.push_back(0);
  for (int i = 1; i < n; i++) {
    fin >> x;
    if (v.size() > k) {
      v.erase(v.begin());
      dp.erase(dp.begin());
    }
    int index = v.size() - 1;
    int best = 0;
    while (index >= 0) {
      int jump = (x - v[index]) * (x - v[index]);
      best = max(dp[index] + jump, best);
      index--;
    }
    ans = max(ans, best);
    v.push_back(x);
    dp.push_back(best);
  }
  fout << ans;
  return 0;
}
