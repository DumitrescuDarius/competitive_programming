#include <bits/stdc++.h>
#include <ios>
#include <vector>
using namespace std;

vector<vector<pair<int, int>>> adj;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  adj.resize(n + 1);
  vector<pair<int, int>> imp;
  for (int i = 1; i < n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x].push_back({y, w});
    if (w == 1)
      imp.push_back({x, y});
  }
  for (auto it : imp) {
    vector<vector<int>> cntByDepthForward(k + 1);
    vector<vector<int>> cntByDepthBackward(k + 1);
    vector<int> seen(n + 1, 0);
  }
}
