#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("iepuri.in");
ofstream fout("iepuri.out");
const int MOD = 30011;

vector<vector<int>> adj;
vector<int> minVal;

void dfs(int node, int val) {
  minVal[node] = val;
  cout << node << "\n";
  for (auto it : adj[node])
    dfs(it, val + 1);
}

int main() {
  int n, k;
  fin >> n >> k;
  adj.resize(n + 1);
  minVal.assign(n + 1, 0);
  vector<int> inDegree(n + 1, 0);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
    inDegree[y]++;
  }
  int root;
  for (int i = 1; i <= n; i++)
    if (inDegree[i] == 0)
      root = i;

  dfs(root, 1);

  for (int i = 1; i <= n; i++)
    cout << minVal[i] << " ";
  return 0;
}

//
//
//
// 0 0 0 1 1 1 1
//
// 1 2 3 4
//
// 1 2 3 4
//
//
// 7
//
// 1
// 1
// 1
// 1
