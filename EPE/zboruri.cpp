#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("zboruri.in");
ofstream fout("zboruri.out");
const int inf = 1e9 + 7;
struct Node {
  int index, weight, price;
  bool operator<(const Node &other) const { return weight < other.weight; }
};
struct costNode {
  int index, price;
  bool operator<(const costNode &other) const { return price < other.price; }
};

vector<vector<Node>> revAdj;
vector<int> dist;

void dfs(int node) {
  int val = dist[node];
  for (auto it : revAdj[node])
    if (dist[it.index] + it.weight == val) {
      dfs(it.index);
      break;
    }
  fout << node << " ";
}
int S;
int minDfs(int node) {
  int val = dist[node];
  int best = inf;
  if (node == S)
    return 0;
  for (auto it : revAdj[node])
    if (dist[it.index] + it.weight == val) {
      best = min(best, it.price + minDfs(it.index));
    }
  return best;
}

int main() {
  int T, n, m, F;
  fin >> T >> n >> m >> S >> F;

  dist.resize(n + 1, inf);
  vector<int> P(n + 1, inf);
  vector<vector<Node>> adj(n + 1);
  revAdj.resize(n + 1);
  priority_queue<Node> pq;

  for (int i = 0; i < m; i++) {
    int x, y, w, p;
    fin >> x >> y >> w >> p;
    adj[x].push_back({y, w, p});
    revAdj[y].push_back({x, w, p});
  }
  if (T == 1) {
    pq.push({S, 0});
    dist[S] = 0;
    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      int index = cur.index;
      int weight = cur.weight;
      if (weight > dist[index])
        continue;
      for (auto it : adj[index]) {
        int newIndex = it.index;
        int newWeight = weight + it.weight;
        if (dist[newIndex] > newWeight) {
          pq.push({newIndex, newWeight});
          dist[newIndex] = newWeight;
        }
      }
    }

    // fout << dist[F];
    if (dist[F] != inf)
      dfs(F);
    else
      fout << -1;
  }
  // if (T == 2) {
  //   pq.push({S, 0, 0});
  //   dist[S] = 0;
  //   P[S] = 0;
  //   while (!pq.empty()) {
  //     Node cur = pq.top();
  //     pq.pop();
  //     int index = cur.index;
  //     int weight = cur.weight;
  //     int price = cur.price;
  //     for (auto it : adj[index]) {
  //       int newIndex = it.index;
  //       int newWeight = weight + it.weight;
  //       int newPrice = price + it.price;
  //       if (dist[newIndex] > newWeight) {
  //         pq.push({newIndex, newWeight, newPrice});
  //         dist[newIndex] = newWeight;
  //         P[newIndex] = min(newWeight, newPrice);
  //       }
  //     }
  //   }
  //   fout << P[F];
  // }
  if (T == 2) {
    pq.push({S, 0});
    dist[S] = 0;
    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      int index = cur.index;
      int weight = cur.weight;
      if (weight > dist[index])
        continue;
      for (auto it : adj[index]) {
        int newIndex = it.index;
        int newWeight = weight + it.weight;
        if (dist[newIndex] > newWeight) {
          pq.push({newIndex, newWeight});
          dist[newIndex] = newWeight;
        }
      }
    }
    if (dist[F] == inf) {
      fout << -1;
      return 0;
    }
    fout << minDfs(F);

    // priority_queue<costNode> npq;
    // npq.push({F, 0});
    // while (!npq.empty()) {
    //   costNode cur = npq.top();
    //   npq.pop();
    //   int index = cur.index;
    //   int weight = cur.price;
    //   int val = dist[index];
    //   if (weight > P[index])
    //     continue;
    //   for (auto it : revAdj[index]) {
    //     if (dist[it.index] + it.weight == val) {
    //       int newIndex = it.index;
    //       int newWeight = weight + it.price;
    //       if (P[newIndex] > newWeight) {
    //         npq.push({newIndex, newWeight});
    //         P[newIndex] = newWeight;
    //       }
    //     }
    //   }
    // }
    // fout << dist[F];
  }

  return 0;
}
