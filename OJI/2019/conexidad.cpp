#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("conexidad.in");
ofstream fout("conexidad.out");
vector<int> adj;
vector<pair<int, int>> ans;
int divide(vector<int> p, int left, int right) {
  if (left == right)
    return 1;
  if (left + 1 == right) {
    adj[left]++;
    adj[right]++;
    ans.push_back({p[left], p[right]});
    return 2;
  }
  int mid = (left + right) / 2;
  adj[mid]++;
  adj[mid + 1]++;
  ans.push_back({p[mid], p[mid + 1]});
  return divide(p, left, mid) + divide(p, mid + 1, right);
}
struct DSU {
  vector<int> parent, rank;
  DSU(int x) {
    parent.resize(x + 1);
    rank.resize(x + 1, 0);
    for (int i = 1; i <= x; i++)
      parent[i] = i;
  }

  int find(int x) {
    if (x == parent[x])
      return x;
    return find(parent[x]);
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
      return 0;

    if (rank[x] < rank[y])
      swap(x, y);
    parent[y] = x;
    if (rank[x] == rank[y])
      rank[x]++;
    return 1;
  }
};
int main() {
  int n, m;
  fin >> n >> m;
  adj.resize(n + 1, 0);
  DSU tree(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    fin >> x >> y;
    tree.unite(x, y);
  }
  vector<int> p, fr(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int parent = tree.find(i);
    if (fr[parent]++ == 0)
      p.push_back(parent);
  }
  fr.erase(fr.begin(), fr.end());

  divide(p, 0, p.size() - 1);
  int maxExtra = 0;
  for (auto it : adj)
    maxExtra = max(maxExtra, it);
  fout << maxExtra << "\n";
  fout << p.size() - 1 << "\n";
  for (auto it : ans)
    fout << it.first << " " << it.second << "\n";
  return 0;
}
