#include <bits/stdc++.h>
#include <fstream>
#include <functional>
#include <queue>
#include <vector>
#define int long long
using namespace std;
ifstream fin("dragoni.in");
ofstream fout("dragoni.out");
const int inf = 1e9 + 7;

struct edge {
  int v;
  int weight;
};

struct path {
  int u;
  int weight;
  int power;

  bool operator<(const path &a) const {
    if (weight != a.weight)
      return weight > a.weight;
    return power < a.power;
  }
};

signed main() {
  int cases;
  int n, m;
  fin >> cases;
  fin >> n >> m;
  vector<int> value(n + 1, 0);
  vector<vector<edge>> adj(n + 1);
  for (int i = 1; i <= n; i++)
    fin >> value[i];
  for (int i = 0; i < m; i++) {
    int u, v, weight;
    fin >> u >> v >> weight;
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
  }
  // read the edges for the adjency list

  if (cases == 1) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;
    vector<int> dist(n + 1, inf);
    int dragonVal = value[1];
    dist[1] = 0;
    q.push({1, 0});
    while (!q.empty()) {
      pair<int, int> node = q.top();
      q.pop();
      int index = node.first;
      int weight = node.second;
      if (weight != dist[index])
        continue;
      for (auto it : adj[index]) {
        if (weight + it.weight < dist[it.v] && it.weight <= dragonVal) {
          dist[it.v] = weight + it.weight;
          q.push({it.v, dist[it.v]});
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
      if (dist[i] != inf)
        ans = max(ans, value[i]);
    fout << ans;
  }
  // for case 1 find the most powerful dragon you can access using the starting
  // dragon

  if (cases == 2) {
    priority_queue<path> q;
    vector<int> dist(n + 1, inf);
    vector<int> maxPower(n + 1, 0);
    // find the smallest distance to the n-th dragon, each dist and maxval
    // represent the minimum distance and the maximum dragon power that you
    // could find

    dist[1] = 0;
    maxPower[1] = value[1];
    q.push({1, 0, value[1]});
    int ans = inf;
    while (!q.empty()) {
      path node = q.top();
      q.pop();
      int index = node.u;
      int weight = node.weight;
      int power = node.power;
      if (weight > dist[index] && power < maxPower[index])
        continue;
      cout << index << " " << weight << " " << power << "\n";
      for (auto it : adj[index]) {
        if (power >= it.weight) {
          int newDist = weight + it.weight;
          int newPower = max(power, value[it.v]);
          if ((newDist < dist[it.v] || newPower > maxPower[it.v])) {
            dist[it.v] = min(dist[it.v], newDist);
            maxPower[it.v] = max(value[it.v], newPower);
            q.push({it.v, newDist, newPower});
          }
        }
      }
    }
    fout << dist[n];
  }

  return 0;
}
