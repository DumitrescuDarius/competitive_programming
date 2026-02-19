#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("bfs.in");
ofstream fout("bfs.out");

vector<int> bfs(int n, int start, vector<vector<int>> &adj) {
  vector<int> dist(n + 1, -1);

  queue<int> q;
  q.push(start);
  dist[start] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (auto it : adj[cur]) {
      if (dist[it] == -1) {
        dist[it] = dist[cur] + 1;
        q.push(it);
      }
    }
  }
  return dist;
}

int main() {
  int n, m, start;

  fin >> n >> m >> start;

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
  }

  vector<int> dist = bfs(n, start, adj);

  for (int i = 1; i <= n; i++)
    fout << dist[i] << " ";
  return 0;
}
