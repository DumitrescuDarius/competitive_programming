#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("numberofpoints.in");
ofstream fout("numberofpoints.out");

vector<int> tree;
int len;

void update(int pos, int val) {
  while (pos <= len) {
    tree[pos] += val;
    pos += (pos & -pos);
  }
}

int query(int pos) {
  int ans = 0;
  while (pos >= 1) {
    ans += tree[pos];
    pos -= (pos & -pos);
  }
  return ans;
}

struct pnt {
  int x, y, index;
};

static bool cmp(pnt a, pnt b) {
  if (a.x == b.x)
    return a.y > b.y;
  return a.x < b.x;
}

signed main() {
  int n, A, B, C, D, x1, y1, x2, y2;
  fin >> n >> A >> B >> C >> D >> x1 >> y1 >> x2 >> y2;
  vector<pnt> points(n + 1);

  points[1] = {x1, y1, 1};
  points[2] = {x2, y2, 2};
  len = max(y1, y2);

  for (int i = 3; i <= n; i++) {
    points[i].x = (points[i - 2].x * A + points[i - 1].x * B + C) % D + 1;
    points[i].y = (points[i - 2].y * A + points[i - 1].y * B + C) % D + 1;
    points[i].index = i;
    len = max(len, points[i].y);
  }
  tree.assign(len + 2, 0);
  sort(points.begin() + 1, points.end(), cmp);
  vector<int> ans(n + 1);
  for (int i = 1; i <= n;) {
    int j;
    for (j = i; j <= n && points[i].x == points[j].x; j++)
      ;
    for (int k = i; k < j; k++)
      ans[points[k].index] = query(points[k].y);
    for (int k = i; k < j; k++)
      update(points[k].y, 1);
    i = j;
  }
  for (int i = 1; i <= n; i++)
    fout << ans[i] << "\n";
  return 0;
}
