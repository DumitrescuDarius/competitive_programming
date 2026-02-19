#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("mos.in");
ofstream fout("mos.out");
ll main() {
  ll n;
  fin >> n;
  vector<vector<ll>> v;
  vector<ll> taken(n + 1, 0), ans(n + 1, 0);
  for (ll i = 1; i <= n; i++) {
    ll a, b;
    fin >> a >> b;
    v.push_back({b, a, i});
  }
  sort(v.begin(), v.end());
  for (auto it : v) {
    ll left = it[1], right = it[0], child = it[2];
    for (ll i = left; i <= right; i++) {
      if (taken[i] == 0) {
        taken[i] = child;
        ans[child] = i;
        break;
      }
    }
  }
  for (ll i = 1; i <= n; i++)
    fout << ans[i] << " ";
}
