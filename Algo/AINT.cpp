#include <bits/stdc++.h>
#include <climits>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("rmq.in");
ofstream fout("rmq.out");
int n, m, ans;
vector<int> tree;

void update(int node, int left, int right, int pos, int val) {
  if (left == right)
    tree[node] = val;
  else {
    int mid = (left + right) / 2;
    if (pos <= mid)
      update(node * 2, left, mid, pos, val);
    else
      update(node * 2 + 1, mid + 1, right, pos, val);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
  }
}

void query(int node, int left, int right, int x, int y) {
  if (x <= left && right <= y)
    ans = min(ans, tree[node]);
  else {
    int mid = (left + right) / 2;
    if (x <= mid)
      query(node * 2, left, mid, x, y);
    if (y > mid)
      query(node * 2 + 1, mid + 1, right, x, y);
  }
}

signed main() {
  int n, q;
  fin >> n >> q;
  tree.resize(n * 4, 0);
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    update(1, 1, n, i, x);
  }
  for (int i = 0; i < q; i++) {
    int x, y;
    fin >> x >> y;
    ans = INT_MAX;
    query(1, 1, n, x, y);
    fout << ans << "\n";
  }
  return 0;
}
