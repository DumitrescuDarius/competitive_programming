#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("iepuri.in");
ofstream fout("iepuri.out");
int maxDpth(vector<vector<int>> adj, int node, int depth) {
  int maxD = 0;
  for (auto it : adj[node])
    maxD = max(maxDpth(adj, it, depth + 1), maxD);
  return maxD;
}
int main() {
  int n, k;
  fin >> n >> k;
  vector<vector<int>> adj(n + 1);
  vector<bool> isRoot(n + 1);
  int sum = 0;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
    isRoot[y] = isRoot[y] | 1;
  }
  int root;
  for (int i = 1; i <= n; i++)
    if (!isRoot[i])
      root = i;
  int maxDepth = maxDpth(adj, root, 1);
  vector<vector<int>> dp(maxDepth + 1, vector<int>(k + 1, 0));
  for (int i = 1; i < maxDepth; i++) {
    for (int j = 1; j <= i; j++) {
      if (i == 1 && j == 1)
        dp[i][j] = 1;
      else
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
    }
  }
  for (int i = 1; i < maxDepth; i++)
    for (int j = 1; j <= i; j++)
      dp[i][j] += dp[i - 1][j];
}
