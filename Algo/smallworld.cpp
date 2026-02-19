#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("smallworld.in");
ofstream fout("smallworld.out");
const int inf = 1e9;
vector<vector<int>> adj;
int n;

int furthestNode(int node) {
  int ans = node, maxVal = -inf;
  vector<int> seen(n + 1, -inf);
  queue<int> q;
  q.push(node);
  seen[node] = 0;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (auto it : adj[cur]) {
      if (seen[it] == -inf) {
        seen[it] = seen[cur] + 1;
        if (seen[it] > maxVal) {
          maxVal = seen[it];
          ans = it;
        }
        q.push(it);
      }
    }
  }
  return ans;
}
vector<int> bfs(int start) {
  vector<int> dist(n + 1, -1);
  queue<int> q;
  q.push(start);
  dist[start] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int v : adj[cur]) {
      if (dist[v] == -1) {
        dist[v] = dist[cur] + 1;
        q.push(v);
      }
    }
  }
  return dist;
}

int main() {
  fin >> n;
  adj.resize(n + 1);
  for (int i = 1; i < n; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  int A = furthestNode(1);
  int B = furthestNode(A);
  vector<int> distA = bfs(A);
  vector<int> distB = bfs(B);

  for (int i = 1; i <= n; i++)
    fout << max(distA[i], distB[i]) << "\n";
}
