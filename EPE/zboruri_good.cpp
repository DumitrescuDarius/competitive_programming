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
  bool operator<(const Node other) const { return other.dist < dist; };
};
vector<vector<Node>> revAdj;
vector<int> D;
void dfs(int nd) {
  int val = D[nd];
  for (auto it : revAdj[nd]) {
    if (D[it.index] + it.dist == val) {
      dfs(it.index);
      break;
    }
  }
  fout << nd << " ";
}
signed main() {
  int T, n, m, S, F;
  fin >> T >> n >> m >> S >> F;
  vector<vector<Node>> adj(n + 1);
  revAdj.resize(n + 1);
  D.resize(n + 1, inf);
  vector<int> P(n + 1, inf);
  D[S] = 0;
  P[S] = 0;
  for (int i = 0; i < m; i++) {
    int x, y, d, p;
    fin >> x >> y >> d >> p;
    adj[x].push_back({y, d, p});
    revAdj[y].push_back({x, d, p});
  }
  priority_queue<Node> pq;
  pq.push({S, 0, 0});

  while (!pq.empty()) {
    Node cur = pq.top();
    int index = cur.index;
    int dist = cur.dist;
    int price = cur.price;
    pq.pop();
    if (dist > D[index])
      continue;
    if (dist == D[index] && price > P[index])
      continue;
    for (auto it : adj[index]) {
      int newIndex = it.index;
      int newDist = dist + it.dist;
      int newPrice = price + it.price;
      if (newDist < D[newIndex]) {
        D[newIndex] = newDist;
        P[newIndex] = newPrice;
        pq.push({newIndex, newDist, newPrice});
      } else if (newDist == D[newIndex] && newPrice < P[newIndex]) {
        P[newIndex] = newPrice;
        pq.push({newIndex, newDist, newPrice});
      }
    }
  }

  if (T == 1) {
    dfs(F);
  }
  if (T == 2) {
    fout << P[F];
  }
  return 0;
}
