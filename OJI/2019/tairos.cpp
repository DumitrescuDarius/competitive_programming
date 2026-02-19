#include <bits/stdc++.h>
#include <queue>
#include <vector>
#define int long long
using namespace std;
ifstream fin("tairos.in");
ofstream fout("tairos.out");
vector<vector<int>> tree;
int d, ans;

void travel(int node, int dist) {
  if (tree[node].empty())
    node = 1;
  if (dist <= d)
    for (auto it : tree[node])
      travel(it, dist + 1);
  else
    ans++;
}
signed main() {
  int n;
  fin >> n >> d;
  vector<vector<int>> adj(n + 1);
  vector<bool> seen(n + 1, 0);
  tree.resize(n + 1);
  for (int i = 0; i < n; i++) {
    int a, b;
    fin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  queue<int> q;
  q.push(1);
  seen[1] = 1;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (auto it : adj[node]) {
      if (!seen[it]) {
        tree[node].push_back(it);
        q.push(it);
        seen[it] = 1;
      }
    }
  }

  travel(1, 1);
  fout << ans;
  return 0;
}
