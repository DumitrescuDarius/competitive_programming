#include <bits/stdc++.h>
#include <vector>
#define int long long
using namespace std;
vector<int> tree;
int n;
void update(int pos, int x) {
  while (pos <= n) {
    tree[pos] += x;
    pos += (pos & -pos);
  }
}
int query(int pos) {
  int sum = 0;
  while (pos > 0) {
    sum += tree[pos];
    pos -= (pos & -pos);
  }
  return sum;
}
signed main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(0);
  int q;
  cin >> n >> q;
  vector<int> v(n + 1, 0);
  tree.resize(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    v[i] = x;
    update(i, x);
  }

  for (int i = 0; i < q; i++) {
    int type, x, y;
    cin >> type >> x >> y;
    if (type == 1) {
      int diff = y - v[x];
      v[x] = y;
      update(x, diff);
    }
    if (type == 2) {
      int ans = query(y) - query(x - 1);
      cout << ans << "\n";
    }
  }
  return 0;
}
