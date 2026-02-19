#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");
const int inf = 1e9 + 7;

struct Edge {
  int y, w;
};

struct Node {
  int index, weight, mask;

  bool operator<(const Node &other) const { return weight > other.weight; }
};

int N;

vector<vector<Edge>> adj;
vector<vector<Edge>> compAdj;

vector<int> dijkstra(int S) {
  priority_queue<Node> pq;
  vector<int> dist(N + 1, inf);
  dist[S] = 0;
  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    int index = cur.index;
    int weight = cur.weight;
    for (auto it : adj[index]) {
      int newIndex = it.y;
      int newWeight = weight + it.w;

      if (newWeight < dist[newIndex]) {
        dist[newIndex] = newWeight;
        pq.push({newIndex, newWeight});
      }
    }
  }
  return dist;
}

int main() {
  int M, k;
  fin >> N >> M;
  fin >> k;

  vector<int> mk(k, 0);
  adj.resize(N + 1);
  compAdj.resize(N + 1);
  set<int> P;
  P.insert(1);
  P.insert(N);
  for (int i = 0; i < k; i++) {
    int x;
    fin >> x;
    mk[x] = (1 << i);
    P.insert(x);
  }

  for (int i = 0; i < M; i++) {
    int x, y, w;
    fin >> x >> y >> w;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
    if ((mk[x] || x == 1 || x == N) && (mk[y] || y == 1 || y == N)) {
      compAdj[x].push_back({y, w});
      compAdj[y].push_back({x, w});
    }
  }

  vector<vector<int>> dist(N + 1);

  for (auto it : P)
    dist[it] = dijkstra(it);

  priority_queue<Node> pq;

  pq.push({1, 0, mk[1]});

  return 0;
}
