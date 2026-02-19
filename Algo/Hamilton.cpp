#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("hamilton.in");
ofstream fout("hamilton.out");
int main() {
  int n, x, y;
  fin >> n;
  vector<vector<int>> adj(n + 1);
  while (fin >> x >> y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  bool dp[1 << 10][10] = {};
  int parent[1 << 10][10] = {};

  dp[1 << 0][0] = 1;

  for (int mask = 0; mask < n; mask++) {
    for (int last = 0; last < n; last++) {
      if (!dp[mask][last])
        continue;
      for (int next = 0; next < n; next++) {
        if (mask & (1 << next))
          continue;
        if (!adj[x])
      }
    }
  }
}
