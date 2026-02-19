#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("summax.in");
ofstream fout("summax.out");
const int bound = 2000000001;
signed main() {
  int cases, n, left, right;
  fin >> cases;
  fin >> n >> left >> right;
  vector<pair<int, int>> prev(n + 2);
  int x;
  int maxVal = 0;
  fin >> x;
  prev[1] = {x, 1};

  for (int i = 2; i <= n; i++) {
    vector<pair<int, int>> cur(n + 2);
    for (int j = 1; j <= i; j++) {
      fin >> x;
      if (prev[j].first == prev[j - 1].first) {
        cur[j].first = prev[j].first + x;
        cur[j].second = min(prev[j].second + prev[j - 1].second, bound);
      }
      if (prev[j].first > prev[j - 1].first) {
        cur[j].first = prev[j].first + x;
        cur[j].second = prev[j].second;
      }
      if (prev[j].first < prev[j - 1].first) {
        cur[j].first = prev[j - 1].first + x;
        cur[j].second = prev[j - 1].second;
      }
      if (i == n)
        maxVal = max(maxVal, cur[j].first);
    }
    prev = cur;
  }

  int ans = 0;

  for (int i = 1; i <= n; i++) {
    if (prev[i].first == maxVal)
      ans = min(ans + prev[i].second, bound);
  }
  fout << ans;
  return 0;
}
