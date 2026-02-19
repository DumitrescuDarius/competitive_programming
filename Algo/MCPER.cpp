#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
class Solution {
private:
  const int inf = 1e9;

  struct Node {
    int index;
    int weight;

    bool operator<(const Node &other) const { return other.weight < weight; }
  };

public:
  int minCost(int n, vector<vector<int>> &edges) {
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < edges.size(); i++) {
      int u = edges[i][0];
      int v = edges[i][1];
      int w = edges[i][2];
      adj[u].push_back({v, w});
      adj[v].push_back({u, 2 * w});
    }

    priority_queue<Node> pq;
    vector<int> dist(n, inf);
    pq.push({0, 0});
    dist[0] = 0;

    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      int index = cur.index;
      int weight = cur.weight;
      if (weight > dist[index])
        continue;
      for (auto it : adj[index]) {
        int newIndex = it.first;
        int newWeight = weight + it.second;
        if (newWeight < dist[newIndex]) {
          dist[newIndex] = newWeight;
          pq.push({newIndex, newWeight});
        }
      }
    }
    return dist[n - 1];
  }
};
