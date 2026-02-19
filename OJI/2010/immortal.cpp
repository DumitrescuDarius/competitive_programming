#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#define int long long
#define pr pair<int, int>
using namespace std;
ifstream fin("immortal.in");
ofstream fout("immortal.out");
vector<pr> delta = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
vector<vector<int>> matrix;
bool inBounds(int x, int y, vector<vector<int>> &matrix) {
  if (x >= 1 && x < matrix.size() && y >= 1 && y < matrix[x].size() &&
      matrix[x][y] == 0)
    return 1;
  return 0;
}
void backTracking(vector<vector<int>> &perm, vector<pair<int, int>> &pos) {
  int ct = 0;

  set<pr> st;
  for (auto &it : pos) {
    int x = it.first, y = it.second;
    if (!matrix[x][y] || st.count({x, y}))
      continue;
    ct++;
    st.insert({x, y});
    for (int i = 0; i < delta.size(); i++) {
      int dx = x + delta[i].first, dy = y + delta[i].second;
      int midx = x + (delta[i].first / 2);
      int midy = y + (delta[i].second / 2);
      if (inBounds(dx, dy, matrix) && matrix[midx][midy] == 1) {
        it = {dx, dy};
        matrix[x][y] = 0;
        matrix[dx][dy] = 1;
        matrix[midx][midy] = 0;
        perm.push_back({x, y, dx, dy});
        backTracking(perm, pos);
        matrix[x][y] = 1;
        matrix[dx][dy] = 0;
        matrix[midx][midy] = 1;
        it = {x, y};
        perm.pop_back();
      }
    }
  }

  if (ct == 1) {
    for (auto it : perm) {
      for (auto jt : it)
        fout << jt << " ";
      fout << "\n";
    }
    exit(0);
  }
}
signed main() {
  int n, m, k;
  fin >> n >> m >> k;
  matrix.resize(n + 1, vector<int>(m + 1, 0));
  vector<pr> pos;
  for (int i = 0; i < k; i++) {
    int x, y;
    fin >> x >> y;
    pos.push_back({x, y});
    matrix[x][y] = 1;
  }
  vector<vector<int>> perm;
  backTracking(perm, pos);

  return 0;
}
