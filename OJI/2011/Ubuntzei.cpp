#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");
const int inf = 1e9 + 7;

struct Node {
  int index, weight, mask;

  bool operator<(const Node &other) const { return other.weight < weight; }
};

signed main() {
  int N, M, K;
  fin >> N >> M;
  fin >> K;
  vector<vector<int>> dist(N + 1, vector<int>((1 << K), inf));
  vector<int> mk(N + 1, 0);

  for (int i = 0; i < K; i++) {
    int x;
    fin >> x;
    mk[x] = (1 << i);
  }
  // for (auto it : mk)
  //   cout << it << " ";
  ;
  vector<vector<pair<int, int>>> adj(N + 1);

  for (int i = 0; i < M; i++) {
    int x, y, w;
    fin >> x >> y >> w;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  priority_queue<Node> pq;
  pq.push({1, 0, mk[1]});
  dist[1][mk[1]] = 0;

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    int index = cur.index;
    int weight = cur.weight;
    int mask = cur.mask;
    if (weight > dist[index][mask])
      continue;
    for (auto it : adj[index]) {
      int newIndex = it.first;
      int newWeight = weight + it.second;
      int newMask = mask | mk[newIndex];
      if (newWeight < dist[newIndex][newMask]) {
        dist[newIndex][newMask] = newWeight;
        pq.push({newIndex, newWeight, newMask});
      }
    }
  }

  fout << dist[N][(1 << K) - 1];

  return 0;
}
