#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("zmeu.in");
ofstream fout("zmeu.out");
const int inf = 1e9 + 7;
int main() {
  int n, p, k, x, y, ans = 0;
  fin >> n >> p >> k;
  fin >> x >> y;
  n -= y;
  ans = x;
  vector<pair<int, int>> str;
  for (int i = 2; i < n; i++) {
    fin >> x >> y;
    str.push_back({x, y});
  }
  fin >> x >> y;
  n -= y;
  ans += x;
  if (n < 0) {
    fout << -1;
    return 0;
  }
  for (int i = 0; i < k; i++) {
    fin >> x >> y;
    if (y == p)
      str[x - 1] = {inf, inf};
  }
  int minTime = inf;
  for (auto it : str) {
    if (it.second < n)
      minTime = min(minTime, it.first);
  }
  if (minTime == inf) {
    fout << -1;
    return 0;
  }
  fout << ans + minTime;
  return 0;
}
