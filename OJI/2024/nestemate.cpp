#include <bits/stdc++.h>
#include <vector>
using namespace std;
ifstream fin("nestemate.in");
ofstream fout("nestemate.out");
void solve() {
  int n, start, finish;
  ;
  fin >> n >> start >> finish;
  vector<int> dist(n + 1, INT_MAX);
  vector<set<int>> adj(n + 1);
  vector<set<int>> lists(500000);
  vector<int> A(n + 1), B(n + 1), C(n + 1);
  for (int i = 1; i <= n; i++) {
    fin >> A[i] >> B[i] >> C[i];
    lists[A[i]].insert(i);
    lists[B[i]].insert(i);
    lists[C[i]].insert(i);
  }
  queue<pair<int, int>> pq;
  pq.push({0, start});
  dist[start] = 0;
  while (!pq.empty()) {
    int d = pq.front().first;
    int node = pq.front().second;
    pq.pop();
    if (d != dist[node])
      continue;
    for (auto it : lists[A[node]])
      if (d + 1 < dist[it]) {
        dist[it] = d + 1;
        pq.push({d + 1, it});
      }
    lists[A[node]].clear();
    for (auto it : lists[B[node]])
      if (d + 1 < dist[it]) {
        dist[it] = d + 1;
        pq.push({d + 1, it});
      }
    lists[B[node]].clear();
    for (auto it : lists[C[node]])
      if (d + 1 < dist[it]) {
        dist[it] = d + 1;
        pq.push({d + 1, it});
      }
    lists[C[node]].clear();
  }
  fout << (dist[finish] != INT_MAX ? dist[finish] : -1);
}
int main() {
  int cases;
  fin >> cases;
  while (cases--) {
    solve();
    fout << "\n";
  }
  return 0;
}
