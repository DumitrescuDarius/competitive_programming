#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("arbint.in");
ofstream fout("arbint.out");

vector<int> tree;

void update(int node, int left, int right, int pos, int val) {

  if (left == right) {
    tree[node] = val;
    return;
  }

  int mid = (left + right) / 2;
  if (pos <= mid)
    update(node * 2, left, mid, pos, val);
  else
    update(node * 2 + 1, mid + 1, right, pos, val);

  tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int ans;
void query(int node, int left, int right, int qleft, int qright) {
  if (left >= qleft && right <= qright) {
    ans = max(ans, tree[node]);
    return;
  }
  if (right < qleft || left > qright)
    return;

  int mid = (left + right) / 2;
  query(node * 2, left, mid, qleft, qright);
  query(node * 2 + 1, mid + 1, right, qleft, qright);

  tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int main() {
  int n, q;
  fin >> n >> q;

  tree.assign(n * 4, 0);

  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    update(1, 1, n, i, x);
  }

  for (auto it : tree)
    cout << it << " ";

  while (q--) {
    int type, a, b;
    fin >> type >> a >> b;
    if (type == 0) {
      ans = 0;
      query(1, 1, n, a, b);
      fout << ans << "\n";
    }
    if (type == 1)
      update(1, 1, n, a, b);
  }
}
