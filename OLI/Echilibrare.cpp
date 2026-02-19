#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
#define ll long long
using namespace std;
ifstream fin("echilibrare.in");
ofstream fout("echilibrare.out");
int main() {
  int n, m;
  ll sum = 0;
  fin >> n >> m;
  vector<vector<int>> adj(n + 1);
  vector<int> seen(n + 1, 0);
  vector<int> value(n + 1);
  vector<ll> zones;
  queue<int> q;

  for (int i = 0; i < m; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  for (int i = 1; i <= n; i++) {
    fin >> value[i];
    sum += value[i];
  }

  seen[1] = 1;
  q.push(1);

  zones.push_back(0);

  while (!q.empty()) {
    int cur = q.front();
    if (zones.size() == seen[cur])
      zones.push_back(0LL);
    zones[seen[cur]] += 1LL * value[cur];
    q.pop();
    for (auto it : adj[cur]) {
      if (!seen[it]) {
        seen[it] = seen[cur] + 1;
        q.push(it);
      }
    }
  }

  ll maxVal = 0;
  int imp = zones.size() - 2;

  for (auto it : zones)
    maxVal = max(maxVal, it);

  fout << zones.back() << "\n";

  ll L = 1, R = sum;
  ll ans = 0;
  while (L <= R) {
    ll mid = (L + R) / 2;
    bool ok = 1;
    ll total = mid * imp;
    if (sum - total < mid)
      ok = 0;
    ll cur = 0;
    for (int i = 1; i < zones.size() - 1; i++) {
      cur += zones[i];
      if (cur >= mid)
        cur = cur - mid;
      else {
        ok = 0;
        break;
      }
    }
    if (ok) {
      L = mid + 1;
      ans = mid;
    } else
      R = mid - 1;
  }
  fout << ans;
  return 0;
}
