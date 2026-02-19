// "ubuntu mid, fedora better"
//                    -Darius Dumitrescu

#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
const int inf = 1e9 + 7;
using namespace std;
ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");

struct Node {
  int index;
  int weight;
  int ubunt;

  bool operator<(const Node &a) const { return weight < a.weight; }
};

int main() {
  int n, m, k, target = 0;
  fin >> n >> m >> k;
  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> dist(n + 1, inf);
  vector<int> ubuntus(n + 1, 0);
  vector<int> loc(n + 1, 0);
  for (int i = 0; i < k; i++) {
    int x;
    fin >> x;
    loc[x] = (1 << i);
    target = target | (1 << i);
  }
  for (int i = 0; i < m; i++) {
    int x, y, d;
    fin >> x >> y >> d;
    adj[x].push_back({y, d});
    adj[y].push_back({x, d});
  }
  priority_queue<Node> pq;
  pq.push({1, 0, loc[1]});
  int ans = inf;
  while (!pq.empty()) {
    Node nd = pq.top();
    pq.pop();
    int index = nd.index;
    int weight = nd.weight;
    int ubunt = nd.ubunt;
    // if (weight != dist[index])
    //   continue;
    for (auto it : adj[index]) {
      int newIndex = it.first;
      int newWeight = weight + it.second;
      int newUbunt = ubunt | loc[newIndex];
      if (newWeight < dist[newIndex] ||
          (newUbunt | ubuntus[newIndex]) != ubuntus[newIndex]) {
        if (newIndex == n && newUbunt == target)
          ans = min(ans, newWeight);
        ubuntus[newIndex] = newUbunt | ubuntus[newIndex];
        dist[newIndex] = min(dist[newIndex], newWeight);
        pq.push({newIndex, newWeight, newUbunt});
      }
    }
  }
  fout << ans;
  return 0;
}
