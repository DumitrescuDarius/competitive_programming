#include <bits/stdc++.h>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
ifstream fin("cerc.in");
ofstream fout("cerc.out");
struct point {
  double left, right;
};
bool cmp(point a, point b) {
  if (a.right == b.right)
    return a.left < b.left;
  return a.right < b.right;
}
int main() {
  int n;
  fin >> n;
  map<double, vector<point>> mp;
  for (int i = 1; i <= n; i++) {
    double x, y, r;
    fin >> x >> y >> r;
    double d = sqrt(x * x + y * y);
    double left = d - r;
    double right = d + r;
    mp[x / y].push_back({left, right});
  }
  fout << mp.size() << " ";
  int ans = 0, k = 0;
  for (auto &[key, value] : mp) {
    sort(value.begin(), value.end(), cmp);
    double start = -1e9;
    int cnt = 0;
    for (auto &[left, right] : value) {
      if (start <= left) {
        start = right;
        cnt++;
      }
    }
    if (cnt > ans) {
      ans = cnt;
      k = 1;
    } else if (cnt == ans)
      k++;
  }
  fout << ans << " " << k;
  return 0;
}
