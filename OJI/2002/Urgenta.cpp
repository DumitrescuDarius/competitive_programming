#include <bits/stdc++.h>
#include <fstream>
#include <utility>
#include <vector>
using namespace std;
ifstream fin("urgenta.in");
ofstream fout("urgenta.out");
struct Edge {
  int u, v, weight;
};

static bool cmp(Edge a, Edge b) { return a.weight < b.weight; }

struct DSU {
  vector<int> rank, parent;
  DSU(int x) {
    rank.resize(x, 0);
    parent.resize(x);
    for (int i = 1; i < x; i++)
      parent[i] = i;
  }

  int find(int &x) {
    if (parent[x] != x)
      return find(parent[x]);
    return x;
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
    return true;
  }
};

int main() {
  int n, m, k;
  fin >> n >> m >> k;
  int cntComps = n;
  int sum = 0;
  vector<Edge> edges(m);
  set<pair<int, int>> ed;
  for (int i = 0; i < m; i++) {
    fin >> edges[i].u >> edges[i].v >> edges[i].weight;
    sum += edges[i].weight;
    ed.insert({edges[i].u, edges[i].v});
  }
  sort(edges.begin(), edges.end(), cmp);
  DSU tree(n + 1);
  vector<pair<int, int>> ans;

  for (auto it : edges) {
    if (cntComps == k) {
      break;
    }
    if (tree.unite(it.u, it.v) == 1) {
      cntComps--;
      sum -= it.weight;
      ans.push_back({it.u, it.v});
      ed.erase({it.u, it.v});
    }
  }
  fout << sum << "\n";
  fout << ed.size() << "\n";
  for (auto it : ed)
    fout << it.first << " " << it.second << "\n";

  return 0;
}
