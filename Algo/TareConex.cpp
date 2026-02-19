#include <bits/stdc++.h>
#include <stack>
#include <vector>
using namespace std;
vector<vector<int>> adj;
vector<bool> onStack;
vector<int> id;
vector<int> low;
stack<int> st;
int cnt, timer;

void dfs(int node) {
  id[node] = low[node] = ++timer;
  st.push(node);
  onStack[node] = 1;

  for (auto it : adj[node]) {
    if (id[it] == -1) {
      dfs(it);
      low[node] = min(low[node], low[it]);
    } else if (onStack[it])
      low[node] = min(low[node], id[it]);
  }

  if (id[node] == low[node]) {
    while (true) {
      int at = st.top();
      st.pop();
      onStack[at] = 0;
      if (node == at)
        break;
    }
    cnt++;
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  adj.assign(n + 1, vector<int>());
  onStack.assign(n + 1, 0);
  id.assign(n + 1, -1);
  low.assign(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  for (int i = 1; i <= n; i++) {
    if (id[i] == -1)
      dfs(i);
  }
  cout << cnt;
  return 0;
}
