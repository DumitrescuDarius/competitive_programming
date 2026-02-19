#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("suma.in");
ofstream fout("suma.out");
const int inf = 1e9 + 7;

vector<vector<int>> delta = {{0, 0}, {-1, -1}, {0, -1}, {-1, 0}};

signed main() {
  int n, total, level = 1, index = 0;
  fin >> n;
  total = n;
  vector<vector<vector<int>>> mat3d;
  vector<vector<vector<int>>> mat3delem;
  vector<int> pref;
  vector<vector<int>> prevDp(level + 2, vector<int>(level + 2, inf));
  fin >> prevDp[1][1];
  mat3d.push_back(prevDp);
  mat3delem.push_back(prevDp);
  pref.push_back(1);
  while (total - level * level > 0) {
    level++;
    total -= level * level;
    int last = pref.back();
    pref.push_back(last + level * level);
    vector<vector<int>> mat(level + 2, vector<int>(level + 2, 0));
    vector<vector<int>> curDp(level + 2, vector<int>(level + 2, inf));
    for (int x = 1; x <= level; x++) {
      for (int y = 1; y <= level; y++) {
        fin >> mat[x][y];
        for (auto it : delta) {
          int dx = x + it[0];
          int dy = y + it[1];
          curDp[x][y] = min(curDp[x][y], mat[x][y] + prevDp[dx][dy]);
        }
      }
    }
    prevDp = curDp;
    mat3d.push_back(prevDp);
    mat3delem.push_back(mat);
  }
  int ans = inf, px, py;
  for (int x = 1; x <= level; x++) {
    for (int y = 1; y <= level; y++) {
      if (prevDp[x][y] < ans) {
        ans = prevDp[x][y];
        px = x;
        py = y;
      }
    }
  }

  fout << level << " " << ans << "\n";
  vector<int> output;

  pref.pop_back();
  for (int k = level - 1; k > 0; k--) {
    int nextX = px, nextY = py;
    output.push_back(pref[k - 1] + (px - 1) * (k + 1) + py);
    for (auto it : delta) {
      int dx = px + it[0];
      int dy = py + it[1];

      if (mat3d[k - 1][dx][dy] + mat3delem[k][px][py] == mat3d[k][px][py]) {
        nextX = dx;
        nextY = dy;
      }
    }
    px = nextX;
    py = nextY;
  }
  output.push_back(1);

  for (int i = output.size() - 1; i >= 0; i--)
    fout << output[i] << " ";
  return 0;
}
