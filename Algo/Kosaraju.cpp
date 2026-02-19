#include <bits/stdc++.h>
#include <vector>
using namespace std;
stack<int> stk;
vector<bool> seen;
vector<bool> reSeen;

void buildStack(int node, vector<vector<int>> &adj) {
  seen[node] = 1;
  for (auto it : adj[node])
    if (!seen[it])
      buildStack(it, adj);
  stk.push(node);
}

void findComp(int node, vector<vector<int>> &adj) {
  reSeen[node] = 1;
  for (auto it : adj[node])
    if (!reSeen[it])
      findComp(it, adj);
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1), reAdj(n + 1);
  seen.assign(n + 1, 0);
  reSeen.assign(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    reAdj[v].push_back(u);
  }

  for (int i = 1; i <= n; i++)
    if (seen[i] == 0)
      buildStack(i, adj);
  int ans = 0;

  while (!stk.empty()) {
    int node = stk.top();
    stk.pop();
    if (reSeen[node] == 0) {
      ans++;
      findComp(node, reAdj);
    }
  }
  cout << ans;
}
