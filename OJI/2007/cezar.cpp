#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("cezar.in");
ofstream fout("cezar.out");

struct Node {
  int index;
  int val;
  int origin;
  bool operator<(const Node &other) const { return val < other.val; }
};

int main() {
  int n, k;
  fin >> n >> k;
  vector<vector<int>> adj(n + 1);
  vector<vector<int>> safe(n + 1);
  vector<int> degree(n + 1, 0);
  vector<int> w(n + 1, 1);
  vector<bool> seen(n + 1, 0);
  queue<int> q;
  for (int i = 1; i < n; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
    degree[x]++;
    degree[y]++;
  }
  for (int i = 1; i <= n; i++) {
    if (degree[i] == 1) {
      q.push(i);
    }
  }
  int ans = 0;
  int maxVal = 0, maxIndex = 0;

  while (!q.empty()) {
    int index = q.front();
    int weight = w[index];
    if (weight > maxVal) {
      maxVal = weight;
      maxIndex = index;
    }

    seen[index] = 1;
    q.pop();
    for (auto it : adj[index]) {
      int newIndex = it;
      if (!seen[newIndex]) {
        w[newIndex] += weight;
        if (--degree[newIndex] == 1)
          q.push({newIndex});
      }
    }
  }

  priority_queue<Node> pq;
  pq.push({maxIndex, 0});
  seen.assign(n + 1, 0);
  k++;

  vector<pair<int, int>> edges;

  while (!pq.empty() && k--) {
    Node cur = pq.top();
    int index = cur.index;
    int weight = cur.val;
    edges.push_back({cur.origin, index});
    seen[index] = 1;
    pq.pop();
    for (auto it : adj[index]) {
      int newIndex = it;
      if (!seen[newIndex])
        pq.push({newIndex, w[newIndex], index});
    }
  }

  for (int i = 1; i < edges.size(); i++)
    safe[edges[i].first].push_back(edges[i].second);

  queue<Node> nq;
  nq.push({maxIndex, 0});
  seen.assign(n + 1, 0);
  seen[maxIndex] = 1;

  while (!nq.empty()) {
    Node cur = nq.front();
    int index = cur.index;
    int weight = cur.val;
    ans += weight;
    nq.pop();
    for (auto it : safe[index]) {
      if (!seen[it]) {
        seen[it] = 1;
        nq.push({it, weight});
      }
    }
    for (auto it : adj[index]) {
      if (!seen[it]) {
        seen[it] = 1;
        nq.push({it, weight + 1});
      }
    }
  }
  fout << ans;

  return 0;
}
