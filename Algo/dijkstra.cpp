#include <bits/stdc++.h>
#include <climits>
#include <fstream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
int main() {
  int n, m;
  fin >> n >> m;
  vector<int> dist(n + 1, INT_MAX);
  vector<vector<pair<int, int>>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    fin >> x >> y >> w;
    adj[x].push_back({w, y});
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, 1});
  dist[1] = 0;
  while (!pq.empty()) {
    int weight = pq.top().first;
    int node = pq.top().second;
    pq.pop();
    if (weight != dist[node])
      continue;
    for (auto it : adj[node]) {
      if (weight + it.first < dist[it.second]) {
        dist[it.second] = weight + it.first;
        pq.push({weight + it.first, it.second});
      }
    }
  }
  for (int i = 2; i <= n; i++)
    if (dist[i] != INT_MAX)
      fout << dist[i] << " ";
    else
      fout << 0 << " ";
  return 0;
}
