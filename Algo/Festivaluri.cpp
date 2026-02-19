#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("festivaluri.in");
ofstream fout("festivaluri.out");
const int inf = 1e9 + 7;
int main() {
  int n, m, p, z, r;
  fin >> n >> m >> p >> z >> r;
  vector<vector<int>> mat(n + 1, vector<int>(n + 1, inf));
  for (int i = 1; i <= n; i++)
    mat[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int x, y, weight;
    fin >> x >> y >> weight;
    mat[x][y] = weight;
  }

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        if (mat[i][k] != inf && mat[k][j] != inf)
          mat[i][j] = min(mat[i][j], mat[k][j] + mat[i][k]);

  int ans = 0;
  vector<int> fest;
  for (int i = 1; i <= r; i++) {
    int x;
    fin >> x;
    fest.push_back(mat[z][x]);
  }
  sort(fest.begin(), fest.end());
  int k = 0;
  while (p >= 0 && k < fest.size()) {
    p -= fest[k];
    k++;
    if (p >= 0)
      ans++;
  }
  fout << ans;
  return 0;
}
