
#include <bits/stdc++.h>
using namespace std;

ifstream fin("lanterna.in");
ofstream fout("lanterna.out");

const int inf = 1e9 + 7;

struct Edge {
  int v, weight, cost;
};

struct Node {
  int index, weight, remain;
};

struct Compare {
  bool operator()(const Node &a, const Node &b) const {
    return a.weight > b.weight; // min-heap by distance
  }
};
vector<bool> replenish;
vector<vector<Edge>> adj;
int n, k;

int calcCost(int battery) {
  const int INF = 1e9;

  vector<vector<int>> dist(n + 1, vector<int>(battery + 1, INF));
  priority_queue<Node, vector<Node>, Compare> pq;

  dist[1][battery] = 0;
  pq.push({1, 0, battery});

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    int u = cur.index;
    int d = cur.weight;
    int bt = cur.remain;

    if (d != dist[u][bt])
      continue;

    for (auto &e : adj[u]) {
      if (bt < e.cost)
        continue;

      int nb = bt - e.cost;
      if (replenish[e.v])
        nb = battery;

      int nd = d + e.weight;

      if (nd < dist[e.v][nb]) {
        dist[e.v][nb] = nd;
        pq.push({e.v, nd, nb});
      }
    }
  }

  int ans = INF;
  for (int b = 0; b <= battery; b++)
    ans = min(ans, dist[n][b]);

  return (ans == INF ? -1 : ans);
}

int bsrch(int target) {
  int left = 1, right = k, ans = -1;

  while (left <= right) {
    int mid = (left + right) / 2;

    int res = calcCost(mid);
    if (res != -1 && res <= target) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return ans;
}

int main() {
  fin >> n >> k;

  replenish.assign(n + 1, false);
  adj.assign(n + 1, {});

  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    replenish[i] = (x == 1);
  }

  int m;
  fin >> m;

  for (int i = 0; i < m; i++) {
    int u, v, w, c;
    fin >> u >> v >> w >> c;
    adj[u].push_back({v, w, c});
    adj[v].push_back({u, w, c});
  }

  int minDist = calcCost(k);
  int minBattery = bsrch(minDist);

  fout << minDist << " " << minBattery;
  return 0;
}
