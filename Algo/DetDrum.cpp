#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
const int inf = 1e9 + 7;
vector<vector<pair<int, int>>> adj;
int n;

vector<int> bfs(int node, int val) {
  vector<int> dist(n + 1, inf);
  queue<pair<int, int>> q;
  q.push({node, val});
  dist[node] = val;
  while (!q.empty()) {
    int index = q.front().first;
    int weight = q.front().second;
    q.pop();
    if (weight > dist[index])
      continue;
    for (auto it : adj[index]) {
      int newIndex = it.first;
      int newWeight = weight + it.second;
      if (newWeight < dist[newIndex]) {
        dist[newIndex] = newWeight;
        q.push({newIndex, newWeight});
      }
    }
  }
  return dist;
}

int main() {
  cin >> n;
  adj.resize(n + 1);
  vector<pair<int, int>> nodes(n + 1);
  int r = -1, val = 0;
  for (int i = 1; i <= n; i++)
    cin >> nodes[i].first;
  for (int i = 1; i <= n; i++) {
    cin >> nodes[i].second;
    int x = nodes[i].first;
    int w = nodes[i].second;
    if (x == 0) {
      r = i;
      val = w;
      continue;
    }
    adj[x].push_back({i, w});
  }
  vector<int> dist = bfs(r, val);
  int maxVal;
  vector<int> ans;

  for (int i = 1; i <= n; i++) {
    if (dist[i] > maxVal) {
      maxVal = dist[i];
      ans.assign({i});
    } else if (dist[i] == maxVal)
      ans.push_back(i);
  }
  cout << maxVal << "\n";
  for (auto it : ans)
    cout << it << " ";
  return 0;
}
