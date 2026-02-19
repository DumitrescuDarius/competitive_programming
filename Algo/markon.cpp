#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("markon.in");
ofstream fout("markon.out");
ll main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n, m, start;
  fin >> n >> m >> start;
  vector<ll> value(n + 1, 0);
  vector<ll> degree(n + 1, 0);
  vector<ull8_t> used(n + 1, 0);
  vector<vector<ll>> adj(n + 1);
  queue<ll> q;

  for (ll i = 1; i <= n; i++)
    fin >> value[i];

  for (ll i = 0; i < m; i++) {
    ll a, b;
    fin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    degree[a]++;
    degree[b]++;
  }

  vector<ll> ans;
  q.push(start);
  used[start] = 1;

  while (!q.empty()) {
    ll node = q.front();
    ans.push_back(node);
    q.pop();
    cout << node << ":\n";
    if (value[node] == 0)
      for (auto it : adj[node]) {
        degree[it]--;
        if (used[it] == 0 || used[it] == 1) {
          cout << it << "\n";
          used[it] = 1;
          q.push(it);
        }
      }
    else
      for (auto it : adj[node]) {
        degree[it]--;
        if (degree[node] < value[node] || used[it] == 1) {
          cout << value[it] << " " << degree[it] << "\n";
          used[it] = 1;
          q.push(it);
        }
      }
  }
  fout << ans.size() << "\n";
  for (ll i = 0; i < ans.size(); i++)
    fout << ans[i] << "\n";

  return 0;
}
