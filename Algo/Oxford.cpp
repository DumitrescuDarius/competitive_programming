#include <bits/stdc++.h>
#include <vector>
using namespace std;
struct Edge {
  int v, w;
};
vector<vector<Edge>> adj, revAdj;
vector<bool> seen;
stack<int> st;

void dfs(int node, vector<vector<Edge>> &ad, int type, bool t) {
  if (t == 0)
    seen[node] = type;
  seen[node] = 1;

  for (auto it : ad[node]) {
    if (!seen[it.v])
      dfs(it.v, ad, t);
  }
  if (t == 0)
    st.push(node);
}

int main() {

  int cases, n, m;
  cin >> cases >> n >> m;
  adj.resize(n + 1);
  revAdj.resize(n + 1);
  seen.resize(n + 1);

  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x].push_back({y, w});
    revAdj[y].push_back({x, w});
  }

  for (int i = 1; i <= n; i++) {
    if (!seen[i])
      dfs(i, adj, 0);
  }
  seen.assign(n + 1, 0);

  while (!st.empty()) {
    int tp = st.top();
    if (!seen[tp]) {
      dfs(tp, revAdj, 1);
    }
  }
}
