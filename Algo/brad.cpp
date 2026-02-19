#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("brad.in");
ofstream fout("brad.out");

vector<ll> found, colors;
bool traverse(ll node, ll color, vector<vector<ll>> &adj) {
  colors[node] = color;
  bool ans = 1;
  for (auto it : adj[node]) {
    if (colors[it] == color)
      ans = 0;
    if (!found[it]) {
      found[it] = 1;
      ans &= traverse(it, color ^ 1, adj);
    }
  }
  return ans;
}

ll main() {
  ll n, m;
  ll cases;
  fin >> cases;
  fin >> n >> m;
  vector<vector<ll>> adj(n + 1);
  for (ll i = 0; i < m; i++) {
    ll a, b;
    fin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  ll ans = 1, cnt0 = 0, cnt1 = 0;
  found.resize(n + 1, 0);
  colors.resize(n + 1, -1);
  for (ll i = 1; i <= n; i++) {
    if (found[i] == 0)
      ans &= traverse(i, 0, adj);
    cnt0 += (colors[i] == 0);
    cnt1 += (colors[i] == 1);
    cout << colors[i];
  }
  if (cases == 1)
    fout << (ans ? "DA" : "NU");
  else {
    ans = 0;
    for (ll i = 1; i <= n; i++) {
      if (colors[i] == 0)
        ans += cnt1 - adj[i].size();
      if (colors[i] == 1)
        ans += cnt0 - adj[i].size();
    }
    fout << ans / 2;
  }
  return 0;
}
