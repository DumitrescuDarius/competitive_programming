#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
ifstream fin("zboruri.in");
ofstream fout("zboruri.out");
const int inf = 1e9 + 7;

struct Node {
  int index, dist, price;
  bool operator<(const Node &other) const { return dist > other.dist; };
};
struct Prices {
  int index, price;
  bool operator<(const Prices &other) const { return price > other.price; };
};
vector<vector<Node>> adj;
vector<vector<Node>> revAdj;
int n;

vector<int> dijkstra(int S) {
  priority_queue<Node> pq;
  vector<int> dist(n + 1, inf);

  pq.push({S, 0});
  dist[S] = 0;

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    int index = cur.index;
    int d = cur.dist;
    if (d > dist[index])
      continue;
    for (auto it : adj[index]) {
      int newIndex = it.index;
      int newD = d + it.dist;
      if (newD < dist[newIndex]) {
        dist[newIndex] = newD;
        pq.push({newIndex, newD});
      }
    }
  }

  return dist;
}

vector<int> dijkstraForPrice(int S, vector<int> &dist) {
  priority_queue<Prices> pq;
  vector<int> P(n + 1, inf);

  pq.push({S, 0});
  P[S] = 0;

  while (!pq.empty()) {
    Prices cur = pq.top();
    pq.pop();
    int index = cur.index;
    int d = cur.price;
    if (d > P[index])
      continue;
    for (auto it : revAdj[index]) {
      if (dist[it.index] + it.dist == dist[index]) {
        int newIndex = it.index;
        int newD = d + it.price;
        if (newD < P[newIndex]) {
          P[newIndex] = newD;
          pq.push({newIndex, newD});
        }
      }
    }
  }

  return P;
}

void reverseRoad(int node, vector<int> &dist) {
  int d = dist[node];
  for (auto it : revAdj[node]) {
    if (dist[it.index] + it.dist == d) {
      reverseRoad(it.index, dist);
      break;
    }
  }
  fout << node << " ";
}

signed main() {
  int T, m, S, F;

  fin >> T >> n >> m >> S >> F;
  adj.resize(n + 1);
  revAdj.resize(n + 1);

  // adding the edges
  for (int i = 0; i < m; i++) {
    int x, y, d, p;
    fin >> x >> y >> d >> p;
    adj[x].push_back({y, d, p});
    revAdj[y].push_back({x, d, p});
  }

  // distance vector to all nodes
  vector<int> dist = dijkstra(S);
  if (dist[F] == inf) {
    fout << -1;
    return 0;
  }

  // testcase 1 where we need the road to a shortest distance road
  if (T == 1) {
    reverseRoad(F, dist);
  }
  if (T == 2) {
    vector<int> prices = dijkstraForPrice(F, dist);
    fout << prices[S];
  }
  return 0;
}
