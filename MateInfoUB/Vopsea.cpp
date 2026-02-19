#include <bits/stdc++.h>
#include <ios>
#include <vector>
using namespace std;
struct Bucket {
  int R, G, B;
};
void btk(vector<Bucket> &part, int pos, Bucket p, vector<Bucket> &comb) {
  if (pos < part.size()) {
    btk(part, pos + 1, p, comb);
    p.R += part[pos].R;
    p.G += part[pos].G;
    p.B += part[pos].B;
    btk(part, pos + 1, p, comb);
  } else
    comb.push_back(p);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, ans = 0;
  cin >> n;
  vector<Bucket> part1, part2, comb1, comb2;
  for (int i = 0; i < n; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    if (i < n / 2)
      part1.push_back({x, y, z});
    else
      part2.push_back({x, y, z});
  }
  Bucket p = {0, 0, 0};
  btk(part1, 0, p, comb1);
  btk(part2, 0, p, comb2);
  map<int, vector<Bucket>> mp;
  for (auto it : comb2) {
    int diff = it.R - it.G;
    mp[diff].push_back(it);
  }
  for (auto it : comb1) {
    int diff = it.G - it.R;
    for (auto jt : mp[diff]) {
      p = {it.R + jt.R, it.G + jt.G, it.B + jt.B};
      if (p.R == p.B && p.B == p.G)
        ans = max(ans, p.R * 3);
    }
  }
  cout << ans;
  return 0;
}
