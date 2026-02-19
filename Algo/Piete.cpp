#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define ll long long
using namespace std;
ifstream fin("piete.in");
ofstream fout("piete.out");
vector<vector<ll>> subsets;
vector<ll> sub;
void backTracking(ll k, ll sum, vector<ll> &v) {
  if (k < v.size()) {
    backTracking(k + 1, sum, v);
    sum += v[k];
    sub.push_back(sum);
    backTracking(k + 1, sum, v);
  }
}
signed main() {
  ll n, m, s, f;
  fin >> n >> m >> s >> f;
  const ll p2n = pow(2, n);

  vector<ll> minVal;
  vector<ll> maxVal;
  for (ll i = 0; i < n; i++) {
    vector<ll> v;
    sub.clear();
    for (ll j = 0; j < m; j++) {
      ll x;
      fin >> x;
      v.push_back(x);
    }
    backTracking(0, 0, v);
    if (minVal.empty()) {
      minVal.assign(sub.begin(), sub.end());
      maxVal.assign(sub.begin(), sub.end());
    }
    for (ll i = 0; i < sub.size(); i++) {
      minVal[i] = min(minVal[i], sub[i]);
      maxVal[i] = max(maxVal[i], sub[i]);
    }
  }
  vector<ll> llervals(10001, 0);
  for (ll i = 0; i < minVal.size(); i++) {
    ll pos = minVal[i];
    ll diff = maxVal[i] - minVal[i];
    llervals[pos] = max(llervals[pos], diff);
  }
  for (ll i = 1; i < llervals.size(); i++)
    llervals[i] = max(llervals[i], llervals[i - 1]);
  ll ans = 0;
  while (s < f) {
    if (llervals[s] == 0) {
      fout << -1;
      return 0;
    }
    ans++;
    s += llervals[s];
  }
  fout << ans;
  return 0;
}
