#include <bits/stdc++.h>
#include <vector>
using namespace std;
ll main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  ll n;
  string s;
  cin >> n >> s;
  ll sz = 1;
  while (sz < n)
    sz <<= 1;
  vector<ll> tree(sz * 2, 0);
  for (ll i = 0; i < n; i++) {
    tree[sz + i] = 1 << (s[i] - 'a');
  }
  for (ll i = sz - 1; i > 0; i--) {
    tree[i] = tree[i << 1] | tree[i << 1 | 1];
  }
  ll q;
  cin >> q;
  for (ll i = 0; i < q; i++) {
    ll op, x;
    cin >> op >> x;
    if (op == 1) {
      char y;
      cin >> y;
      --x;
      ll pos = sz + x;
      tree[pos] = 1 << (y - 'a');
      for (pos >>= 1; pos > 0; pos >>= 1) {
        tree[pos] = tree[pos << 1] | tree[pos << 1 | 1];
      }
    } else {
      ll y;
      cin >> y;
      ll left = --x + sz;
      ll right = --y + sz;
      ll mask = 0;
      while (left <= right) {
        if (left & 1)
          mask |= tree[left++];
        if (!(right & 1))
          mask |= tree[right--];
        left >>= 1;
        right >>= 1;
      }
      cout << __builtin_popcount(mask) << "\n";
    }
  }
  return 0;
}
