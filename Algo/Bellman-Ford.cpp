#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
#define pr pair<int, int>
using namespace std;
ifstream fin("bellmangord.in");
ifstream fout("bellmangord.out");
bool check_cycle(vector<vector<pr>> &adj) {
  queue<pr> q;

  q.push({0, 0});
  while (!q.empty()) {
    pr node = q.front();
    int index = node.first;
    int cost = node.second;
    for (auto it : adj[]) {
    }
  }
}
int main() {
  int n;
  fin >> n;
  vector<vector<pr>> adj(n + 1);
  for (int i = 0; i < n; i++) {
    int x, y, cost;
    fin >> x >> y >> cost;
    adj[x].push_back({y, cost});
  }
  check_cycle();
  queue<int> q;
  while (!q.empty()) {
  }
}
