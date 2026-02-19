#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("ateleport.in");
ofstream fout("ateleport.out");
const int inf = 1e9 + 7;
int N, L;

struct Node {
  int index, weight, teleports;
  bool operator<(const Node &other) const { return weight > other.weight; }
};

vector<vector<int>> canAccess;
vector<bool> computed;

vector<vector<pair<int, int>>> adj;

// function for finding the furthest accesible nodes using bfs and saving them
// into canAcess

vector<int> furthest(int S) {
  if (!computed[S]) {
    computed[S] = 1;
    vector<int> seen(N + 1, 0);
    vector<int> output;
    queue<int> q;
    q.push(S);
    seen[S] = 1;
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      if (seen[cur] > L + 1)
        continue;
      output.push_back(cur);
      for (auto it : adj[cur]) {
        int newNode = it.first;
        if (!seen[newNode]) {
          seen[newNode] = seen[cur] + 1;
          q.push(newNode);
        }
      }
    }
    canAccess[S] = output;
  }
  return canAccess[S];
}

int main() {

  int M, P, K;
  fin >> N >> M >> P >> L >> K;

  adj.resize(N + 1);
  computed.resize(N + 1, 0);
  canAccess.resize(N + 1);

  for (int i = 0; i < M; i++) {
    int x, y, w;
    fin >> x >> y >> w;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  priority_queue<Node> pq;
  vector<vector<int>> dist(N + 1, vector<int>(K + 1, inf));
  pq.push({1, 0, K});
  dist[1][K] = 0;

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    int index = cur.index;
    int weight = cur.weight;
    int teleports = cur.teleports;

    if (dist[index][teleports] < weight)
      continue;

    for (auto it : adj[index]) {
      int newIndex = it.first;
      int newWeight = weight + it.second;

      if (newWeight < dist[newIndex][teleports]) {
        dist[newIndex][teleports] = newWeight;
        pq.push({newIndex, newWeight, teleports});
      }
    }

    if (teleports == 0)
      continue;

    vector<int> reachable = furthest(index);

    for (auto it : reachable) {
      int newIndex = it;
      int newWeight = weight + P;
      int newTeleports = teleports - 1;

      if (newWeight < dist[newIndex][newTeleports]) {
        dist[newIndex][newTeleports] = newWeight;
        pq.push({newIndex, newWeight, newTeleports});
      }
    }
  }

  int ans = inf;
  for (int i = 0; i <= K; i++)
    ans = min(ans, dist[N][i]);

  fout << ans;

  return 0;
}
