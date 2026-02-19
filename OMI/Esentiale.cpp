#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("esentiale.in");
ofstream fout("esentiale.out");

struct Edges {
  int x;
  int y;
  int w;
};

bool cmp(Edges a, Edges b) { return a.w < b.w; }

struct DSU {
  vector<int> rank, parents;
  DSU(int x) {
    rank.resize(x + 1, 0);
    parents.resize(x + 1, 0);
    for (int i = 0; i <= x; i++)
      parents[i] = i;
  }

  int find(int x) {
    if (parents[x] != x)
      return find(parents[x]);
    return parents[x];
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
      return 0;

    if (rank[x] < rank[y])
      swap(x, y);

    parents[y] = x;

    if (rank[x] == rank[y])
      rank[x]++;

    return 1;
  }
};

int main() {

  int n, m, T;

  fin >> n >> m >> T;

  if (T == 1) {
    DSU tree(n);
    vector<Edges> ed;
    for (int i = 0; i < m; i++) {
      int x, y, w;
      fin >> x >> y >> w;
      ed.push_back({x, y, w});
    }
    sort(ed.begin(), ed.end(), cmp);

    int ans = 0;
    for (int i = 0; i < m; i++) {
      int x, y, w;
      x = ed[i].x;
      y = ed[i].y;
      w = ed[i].w;
      if (tree.unite(x, y))
        ans += w;
    }
    fout << ans;
  }
  map<int, set<int>> mp;
  vector<int> isGood(n + 1, 1);
  if (T == 2) {
    DSU tree(n);
    vector<Edges> ed;
    for (int i = 0; i < m; i++) {
      int x, y, w;
      fin >> x >> y >> w;
      ed.push_back({x, y, w});
    }
    sort(ed.begin(), ed.end(), cmp);

    int ans = 0;
    for (int i = 0; i < m; i++) {
      int x, y, w;
      x = ed[i].x;
      y = ed[i].y;
      w = ed[i].w;
      if (tree.unite(x, y)) {
        mp[x].insert(w);
        mp[y].insert(w);
      } else {
        if (mp[x].count(w)) {
          isGood[x] = 0;
          isGood[y] = 0;
        }
      }
    }
    fout << ans;
  }
  return 0;
}
