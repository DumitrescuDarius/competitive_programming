#include <bits/stdc++.h>
#include <vector>
using namespace std;
vector<vector<int>> adj, revAdj;
vector<int> seen;
stack<int> st;

void dfs(int node) {
  seen[node] = 1;
  for (auto it : adj[node])
    if (!seen[it])
      dfs(it);
  st.push(node);
}
void reDfs(int node, int color) {
  seen[node] = color;
  for (auto it : revAdj[node])
    if (!seen[it])
      reDfs(it, color);
}

int main() {
  int n, m;
  cin >> n >> m;
  adj.resize(n + 1);
  revAdj.resize(n + 1);
  seen.resize(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    revAdj[y].push_back(x);
  }

  for (int i = 1; i <= n; i++) {
    if (!seen[i])
      dfs(i);
  }
  seen.assign(n + 1, 0);
  int color = 0;
  while (!st.empty()) {
    int node = st.top();
    st.pop();
    if (!seen[node])
      reDfs(node, ++color);
  }
  map<int, int> mp;
  for (int i = 1; i <= n; i++)
    mp[seen[i]]++;
  int ans = 0;
  for (auto it : mp) {
    if (it.second == 1)
      ans++;
  }
  cout << ans;
  return 0;
}
