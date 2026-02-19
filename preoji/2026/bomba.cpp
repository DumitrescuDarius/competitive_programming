
#include <bits/stdc++.h>
using namespace std;

ifstream fin("bomba.in");
ofstream fout("bomba.out");

int main() {
  int n, m;
  fin >> n >> m;

  vector<vector<int>> adj(n + 1);
  vector<int> inDegree(n + 1, 0);

  vector<int> L(n + 1, 1);
  vector<int> R(n + 1, n);

  for (int i = 0; i < m; i++) {
    int t, a, b;
    fin >> t >> a >> b;

    if (t == 1) {
      adj[a].push_back(b);
      inDegree[b]++;
    }
    if (t == 2) {
      adj[b].push_back(a);
      inDegree[a]++;
    }
    if (t == 3)
      L[a] = max(L[a], b);
    if (t == 4)
      R[a] = min(R[a], b);
  }

  for (int i = 1; i <= n; i++) {
    if (L[i] > R[i]) {
      fout << "Imposibil";
      return 0;
    }
  }

  queue<int> q;
  vector<int> topo;
  vector<int> deg = inDegree;

  for (int i = 1; i <= n; i++)
    if (deg[i] == 0)
      q.push(i);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.push_back(u);

    for (auto v : adj[u]) {
      deg[v]--;
      if (deg[v] == 0)
        q.push(v);
    }
  }

  if ((int)topo.size() != n) {
    fout << "Imposibil";
    return 0;
  }

  for (auto u : topo)
    for (auto v : adj[u])
      L[v] = max(L[v], L[u] + 1);

  for (int i = n - 1; i >= 0; i--) {
    int u = topo[i];
    for (auto v : adj[u])
      R[u] = min(R[u], R[v] - 1);
  }

  // verificare dupa propagare
  for (int i = 1; i <= n; i++) {
    if (L[i] > R[i]) {
      fout << "Imposibil";
      return 0;
    }
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq_all; // sortat dupa L

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq_ready; // sortat dupa R

  for (int i = 1; i <= n; i++)
    if (inDegree[i] == 0)
      pq_all.push({L[i], i});

  vector<int> ans;

  for (int time = 1; time <= n; time++) {

    // mutam nodurile activate
    while (!pq_all.empty() && pq_all.top().first <= time) {
      auto [l, node] = pq_all.top();
      pq_all.pop();
      pq_ready.push({R[node], node});
    }

    if (pq_ready.empty()) {
      fout << "Imposibil";
      return 0;
    }

    auto [deadline, node] = pq_ready.top();
    pq_ready.pop();

    if (time > deadline) {
      fout << "Imposibil";
      return 0;
    }

    ans.push_back(node);

    for (auto nxt : adj[node]) {
      inDegree[nxt]--;
      if (inDegree[nxt] == 0)
        pq_all.push({L[nxt], nxt});
    }
  }

  for (auto x : ans)
    fout << x << " ";
}
