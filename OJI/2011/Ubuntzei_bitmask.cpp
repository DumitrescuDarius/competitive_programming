#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");
const int inf = 1e9 + 7;
struct Node {
  int index, weight;

  bool operator<(const Node &other) const { return weight > other.weight; }
};

int N;

vector<vector<pair<int, int>>> adj;
vector<vector<int>> impAdj;
set<int> imp;

vector<int> dijkstra(int S) {
  priority_queue<Node> pq;
  vector<int> dist(N + 1, inf);
  dist[S] = 0;
  pq.push({S, 0});

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

  vector<int> output;
  for (auto it : imp) {
    output.push_back(dist[it]);
  }

  return output;
}

int main() {
  int M, K;
  fin >> N >> M;
  adj.resize(N + 1);
  fin >> K;

  imp.insert(1);
  imp.insert(N);
  for (int i = 1; i <= K; i++) {
    int x;
    fin >> x;
    imp.insert(x);
  }

  int nrImp = imp.size();

  for (int i = 0; i < M; i++) {
    int x, y, w;
    fin >> x >> y >> w;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  vector<vector<int>> dp(1 << nrImp, vector<int>(nrImp, inf));
  for (auto it : imp)
    impAdj.push_back(dijkstra(it));

  dp[1][0] = 0;
  for (int mask = 0; mask < (1 << nrImp); mask++) {
    for (int x = 0; x < nrImp; x++) {
      if (!(mask & (1 << x)))
        continue;

      if (dp[mask][x] == inf)
        continue;

      for (int y = 0; y < nrImp; y++) {
        if (mask & (1 << y))
          continue;

        int newMask = mask | (1 << y);

        dp[newMask][y] = min(dp[newMask][y], dp[mask][x] + impAdj[x][y]);
      }
    }
  }

  fout << dp[(1 << nrImp) - 1][nrImp - 1];

  return 0;
}
