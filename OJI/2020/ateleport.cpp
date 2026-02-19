#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("ateleport.in");
ofstream fout("ateleport.out");
const int inf = 1e9 + 7;

struct Node {
  int index;
  int weight;
  int remain;
  int pass;

  bool operator<(const Node &other) const { return weight < other.weight; }
};

int main() {
  int n, m, fast, total, k;
  fin >> n >> m >> fast >> total >> k;
  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> dist(n + 1, inf);
  vector<int> trav(n + 1, 0);
  vector<int> jumps(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int x, y, d;
    fin >> x >> y >> d;
    adj[x].push_back({y, d});
    adj[y].push_back({x, d});
  }

  priority_queue<Node> pq;
  pq.push({1, 0, k, total});
  dist[1] = 0;
  trav[1] = k;
  jumps[1] = total;

  while (!pq.empty()) {
    Node nd = pq.top();
    pq.pop();
    int index = nd.index;
    int weight = nd.weight;
    int remain = nd.remain;
    int pass = nd.pass;
    if (weight >= dist[index] && remain <= trav[index] && pass < jumps[index])
      continue;
    for (auto it : adj[index]) {
      int newIndex = it.first;
      int newWeightA = weight + it.second;
      int newRemainA = remain;
      int newWeightB = weight + fast;
      int newRemainB = remain - 1;
      int newPass = pass - 1;

      if (newPass >= 0) {
        if (newWeightA < dist[newIndex] || newRemainA > trav[newIndex] ||
            newPass > jumps[newIndex]) {
          dist[newIndex] = min(dist[newIndex], newWeightA);
          trav[newIndex] = max(trav[newIndex], newRemainA);
          jumps[newIndex] = max(jumps[newIndex], newPass);
          pq.push({newIndex, newWeightA, newRemainA, newPass});
        }
        if (remain > 0) {
          if (newWeightB < dist[newIndex] || newRemainB > trav[newIndex] ||
              newPass > jumps[newIndex]) {
            dist[newIndex] = min(dist[newIndex], newWeightB);
            trav[newIndex] = max(trav[newIndex], newRemainB);
            jumps[newIndex] = max(jumps[newIndex], newPass);
            pq.push({newIndex, newWeightB, newRemainB, newPass});
          }
        }
      }
    }
  }
  for (auto it : dist)
    cout << it << " ";

  fout << dist[n];
  return 0;
}
