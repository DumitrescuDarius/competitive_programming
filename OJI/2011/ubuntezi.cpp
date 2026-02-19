// Din pacate ubuntzeii s-au mutat la Linux Fedora din cauza pachetelor snap

#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");
const int inf = 1e9 + 7;

struct Node {
  int index;
  int dt;
  set<int> st;

  bool operator<(const Node &other) const { return dt > other.dt; }
};
int main() {
  int n, m, k;
  fin >> n >> m;
  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> imp(n + 1, 0), dist(n + 1, inf), ubunt(n + 1, 0);
  fin >> k;
  for (int i = 1; i <= k; i++) {
    int x;
    fin >> x;
    imp[x]++;
  }
  for (int i = 0; i < m; i++) {
    int x, y, dist;
    fin >> x >> y >> dist;
    adj[x].push_back({y, dist});
    adj[y].push_back({x, dist});
  }
  priority_queue<Node> q;
  q.push({1, 1});
  dist[1] = 1;
  if (imp[1] == 1) {
    set<int> newSet;
    newSet.insert(1);
    q.pop();
    q.push({1, 1, newSet});
  }
  // dijkstra on state based on distance, prev points, and a check of points
  // taken so far
  while (!q.empty()) {
    Node curr = q.top();
    q.pop();
    int index = curr.index;
    int dt = curr.dt;
    set<int> st = curr.st;
    // curr node data
    if (dt != dist[index] || st.size() != ubunt[index])
      continue;
    for (auto it : adj[index]) {
      int newIndex = it.first;
      int newDt = dt + it.second;
      set<int> newSt = st;
      if (imp[newIndex])
        newSt.insert(newIndex);
      // next node data
      if (newDt < dist[newIndex] || newSt.size() > ubunt[newIndex]) {
        dist[newIndex] = min(newDt, dist[newIndex]);
        ubunt[newIndex] = max((int)st.size(), ubunt[newIndex]);
        q.push({newIndex, newDt, newSt});
      }
    }
  }
  for (int i = 1; i <= n; i++)
    cout << dist[i] << " ";
  fout << dist[n];
  return 0;
}
