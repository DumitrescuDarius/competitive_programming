#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("gcd2.in");
ofstream fout("gcd2.out");
vector<int> tree;
vector<int> v;

int GCD(int a, int b) {
  while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void build(int node, int left, int right) {
  if (left == right) {
    tree[node] = v[left];
    return;
  }
  int mid = (left + right) / 2;
  build(node * 2, left, mid);
  build(node * 2 + 1, mid + 1, right);
  tree[node] = GCD(tree[node * 2], tree[node * 2 + 1]);
}

int g;
void query(int node, int left, int right, int qleft, int qright) {
  if (qleft <= left && right <= qright) {
    g = GCD(g, tree[node]);
    return;
  } else if (qleft > right || qright < left)
    return;
  int mid = (left + right) / 2;
  query(node * 2, left, mid, qleft, qright);
  query(node * 2 + 1, mid + 1, right, qleft, qright);
}

signed main() {
  int n, ans = 0;
  fin >> n;
  tree.resize(n * 4, 0);
  v.resize(n + 1, 0);
  for (int i = 1; i <= n; i++)
    fin >> v[i];
  build(1, 1, n);
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      g = v[i];
      query(1, 1, n, i, j);
      ans += g;
      if (g == 1) {
        ans += n - j;
        break;
      }
    }
  }
  fout << ans;
  return 0;
}
