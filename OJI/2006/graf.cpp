#include <bits/stdc++.h>
#include <fstream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");
const int inf = 1e9 + 7;

vector<vector<int>> adj;
vector<bool> seen;

vector<int> goBack(vector<int> &dist, int start, int finish) {
  vector<int> fr(adj.size(), 0);
  queue<int> q;
  q.push(finish);
  seen[finish] = 1;

  while (!q.empty()) {
    int node = q.front();
    int weight = dist[node];
    q.pop();
    cout << node << " ";
    fr[weight]++;
    for (auto it : adj[node])
      if (dist[it] + 1 == dist[node] && seen[it] == 0) {
        q.push(it);
        seen[it] = 1;
      }
  }
  return fr;
}

vector<int> dijkstra(int start) {
  vector<int> dist(adj.size(), inf);
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  pq.push({0, start});
  dist[start] = 0;
  while (!pq.empty()) {
    pair<int, int> node = pq.top();
    int weight = node.first;
    int index = node.second;
    pq.pop();
    if (dist[index] != weight)
      continue;
    for (auto it : adj[index]) {
      if (weight + 1 < dist[it]) {
        dist[it] = weight + 1;
        pq.push({weight + 1, it});
      }
    }
  }
  return dist;
}
int main() {
  int n, m, x, y;
  fin >> n >> m >> x >> y;
  seen.assign(n + 1, 0);
  adj.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    fin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> dist = dijkstra(x);
  vector<int> fr = goBack(dist, x, y);

  vector<int> ans;
  for (int i = 1; i <= n; i++)
    if (fr[dist[i]] == 1 && seen[i])
      ans.push_back(i);

  fout << ans.size() << "\n";
  for (auto it : ans)
    fout << it << " ";

  return 0;
}
