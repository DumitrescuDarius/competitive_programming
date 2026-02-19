#include <bits/stdc++.h>
using namespace std;
ifstream fin("aemi.in");
ofstream fout("aemi.out");
vector<int> tree;
int ans;
void update(int node, int left, int right, int pos, int val) {
  if (left == right)
    tree[node] = val;
  if (left < right) {
    int mid = (left + right) / 2;
    if (pos <= mid)
      update(node << 1, left, mid, pos, val);
    else
      update((node << 1) + 1, mid + 1, right, pos, val);
    tree[node] = min(tree[node << 1], tree[(node << 1) + 1]);
  }
}
void query(int node, int left, int right, int x, int y) {
  if (right < x || left > y)
    return;
  if (x <= left && right <= y)
    ans = min(ans, tree[node]);
  if (left < right) {
    int mid = (left + right) / 2;
    if (x <= mid)
      query(node << 1, left, mid, x, y);
    if (y > mid)
      query((node << 1) + 1, mid + 1, right, x, y);
  }
}

int main() {
  int n;
  fin >> n;
  tree.resize(n * 4, 0);
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    update(1, 1, n, i, x);
  }
  int q;
  fin >> q;
  for (int i = 0; i < q; i++) {
    int type, x, y;
    fin >> type >> x >> y;
    if (type == 1) {
      ans = INT_MAX;
      query(1, 1, n, x, y);
      fout << ans << "\n";
    }
    if (type == 2)
      update(1, 1, n, x, y);
  }
  return 0;
}
