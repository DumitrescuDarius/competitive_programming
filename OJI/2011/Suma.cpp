#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("suma.in");
ofstream fout("suma.out");
const int inf = 1e9 + 7;

vector<vector<int>> delta = {
    {-1, -1, -1}, {-1, 0, -1}, {-1, -1, 0}, {-1, 0, 0}};

int main() {
  int pir[50][50][50] = {};
  int dp[50][50][50] = {};
  int n;
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      for (int k = 0; k < 50; k++)
        dp[i][j][k] = inf;

  fin >> n;
  int index = 0, p = 1, k = 1;
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    pir[k][index / k + 1][index % k + 1] = x;
    index++;
    if (index == p) {
      index = 0;
      k++;
      p = k * k;
    }
  }
  fout << k - 1 << " ";
  int ans = inf;
  dp[1][1][1] = pir[1][1][1];
  for (int z = 2; z < k; z++) {
    p = z * z;
    for (int x = 1; x <= k; x++) {
      for (int y = 1; y <= k; y++) {
        for (auto it : delta) {
          int dz = z + it[0];
          int dx = x + it[1];
          int dy = y + it[2];
          int dist = pir[z][x][y] + dp[dz][dx][dy];
          dp[z][x][y] = min(dp[z][x][y], dist);
        }
        if (z == k)
          ans = min(ans, dp[z][x][y]);
        cout << dp[z][x][y] << " ";
      }
    }
    cout << "\n";
  }
  // fout << ans;
  return 0;
}
