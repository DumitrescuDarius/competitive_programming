
#include <bits/stdc++.h>
using namespace std;

ifstream fin("markdown.in");
ofstream fout("markdown.out");

ll main() {
  ll n, m, start;
  fin >> n >> m >> start;

  vector<ll> value(n + 1);
  vector<ll> degree(n + 1);
  vector<ull8_t> used(n + 1, 0);

  for (ll i = 1; i <= n; i++)
    fin >> value[i];

  vector<ll> head(n + 1, -1);
  vector<ll> to(2 * m);
  vector<ll> nxt(2 * m);

  ll idx = 0;
  auto add_edge = [&](ll a, ll b) {
    to[idx] = b;
    nxt[idx] = head[a];
    head[a] = idx++;
  };

  for (ll i = 0; i < m; i++) {
    ll a, b;
    fin >> a >> b;
    add_edge(a, b);
    add_edge(b, a);
    degree[a]++;
    degree[b]++;
  }

  queue<ll> q;
  vector<ll> ans;

  q.push(start);
  used[start] = 1;

  while (!q.empty()) {
    ll node = q.front();
    q.pop();
    ans.push_back(node);

    if (value[node] == 0) {
      for (ll e = head[node]; e != -1; e = nxt[e]) {
        ll v = to[e];
        if (!used[v]) {
          used[v] = 1;
          q.push(v);
        }
      }
    } else {
      for (ll e = head[node]; e != -1; e = nxt[e]) {
        ll v = to[e];
        if (!used[v] && --degree[v] < value[node]) {
          used[v] = 1;
          q.push(v);
        }
      }
    }
  }

  fout << ans.size() << "\n";
  for (ll x : ans)
    fout << x << "\n";

  return 0;
}
