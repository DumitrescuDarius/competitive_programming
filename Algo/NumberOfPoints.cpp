#include <bits/stdc++.h>
#include <vector>
#define ll long long
using namespace std;
ifstream fin("numberofpolls.in");
ofstream fout("numberofpolls.out");

vector<ll> tree;
ll len;

struct poll {
  ll x, y, idx;
};

void update(ll pos, ll val) {
  while (pos <= len) {
    tree[pos] += val;
    pos += (pos & (-pos));
  }
}

ll query(ll pos) {
  ll s = 0;
  while (pos > 0) {
    s += tree[pos];
    pos -= (pos & (-pos));
  }
  return s;
}

signed main() {
  ll n, a, b, c, d, x1, y1, x2, y2;
  fin >> n >> a >> b >> c >> d >> x1 >> y1 >> x2 >> y2;
  vector<poll> polls(n + 1);
  polls[1] = {x1, y1, 1};
  polls[2] = {x2, y2, 2};
  len = max(y1, y2);
  for (ll i = 3; i <= n; i++) {
    ll xi = (polls[i - 2].x * a + polls[i - 1].x * b + c) % d + 1;
    ll yi = (polls[i - 2].y * a + polls[i - 1].y * b + c) % d + 1;
    polls[i] = {xi, yi, i};
    len = max(len, polls[i].y);
  }
  sort(polls.begin() + 1, polls.end(), [](const poll &a, const poll &b) {
    if (a.x != b.x)
      return a.x < b.x;
    return a.y < b.y;
  });
  tree.resize(len + 1, 0);
  vector<ll> ans(n + 1, 0);

  for (ll i = 1; i <= n;) {
    ll j;
    for (j = i; j <= n && polls[i].x == polls[j].x; j++)
      ;
    for (ll k = i; k < j; k++)
      ans[polls[k].idx] = query(polls[k].y);

    for (ll k = i; k < j; k++)
      update(polls[k].y, 1);
    i = j;
  }
  for (ll i = 1; i < ans.size(); i++)
    fout << ans[i] << "\n";
  return 0;
}
