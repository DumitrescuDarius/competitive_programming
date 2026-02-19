#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("aint.in");
ofstream fout("aint.out");
const int inf = 1e9 + 7;
vector<int> tree;
vector<int> v;

void build(int node, int left, int right) {
  if (left == right)
    tree[node] = v[left];
  else {
    int mid = (left + right) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
  }
}

void update(int node, int left, int right, int pos, int val) {
  if (left == right)
    tree[node] = val;
  else {
    int mid = (left + right) / 2;
    if (mid >= pos)
      update(node * 2, left, mid, pos, val);
    else
      update(node * 2 + 1, mid + 1, right, pos, val);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
  }
}

int query(int node, int left, int right, int qleft, int qright) {
  if (right < qleft || left > qright)   // no overlap
    return inf;                         // identity for min
  if (left >= qleft && right <= qright) // total overlap
    return tree[node];
  int mid = left + (right - left) / 2;
  int leftMin = query(node * 2, left, mid, qleft, qright);
  int rightMin = query(node * 2 + 1, mid + 1, right, qleft, qright);
  return min(leftMin, rightMin); // combine results
}

int main() {
  int n, q;
  fin >> n >> q;
  v.assign(n + 1, 0);
  tree.assign(n * 4, 0);
  for (int i = 1; i <= n; i++)
    fin >> v[i];

  build(1, 1, n);

  for (int i = 0; i < q; i++) {
    int type, x, y;
    fin >> type >> x >> y;
    if (type == 1)
      update(1, 1, n, x, y);
    else {
      fout << query(1, 1, n, x, y) << "\n";
    }
  }
  return 0;
}
