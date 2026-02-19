#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("picard.in");
ofstream fout("picard.out");
const int inf = 1e9 + 7;
int main() {
  int n, m;
  fin >> n >> m;
  vector<vector<int>> mat(n + 1, vector<int>(m + 1, inf));
  for (int i = 1; i <= n; i++)
    mat[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int x, y, w;
    fin >> x >> y >> w;
    mat[x][y] = w;
    mat[y][x] = w;
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (mat[i][k] == inf || mat[k][i] == inf)
          continue;
        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
      }
    }
  }

  int maxVal = 0;
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
      if (mat[i][j] != inf)
        sum += mat[i][j];
    }
    if (sum > maxVal) {
      maxVal = sum;
      ans.clear();
      ans.push_back(i);
    } else if (sum == maxVal)
      ans.push_back(i);
  }
  for (auto it : ans)
    fout << it << " ";
  return 0;
}

// 5 + 4 + 5 + 7 + 7 =
