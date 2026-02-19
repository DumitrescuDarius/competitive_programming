#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("chinteni.in");
ofstream fout("chinteni.out");
vector<pair<int, int>> delta = {{-1, 0}, {-1, -1}, {-1, 1}};
const int inf = 1e9;
int n, m;
bool inBounds(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < m)
    return 1;
  return 0;
}
int main() {
  fin >> n >> m;
  vector<vector<int>> mat(n, vector<int>(m));
  vector<vector<int>> dp(n, vector<int>(m));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      fin >> mat[i][j];
  for (int i = 0; i < m; i++)
    dp[0][i] = mat[0][i];
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      dp[i][j] = -inf;
      for (auto it : delta) {
        int dx = i + it.first;
        int dy = j + it.second;
        if (inBounds(dx, dy) && mat[dx][dy] % 2 != mat[i][j] % 2)
          dp[i][j] = max(dp[i][j], dp[dx][dy] + mat[i][j]);
      }
      cout << dp[i][j] << " ";
    }
    cout << "\n";
  }
  int ans = -inf;
  for (int i = 0; i < m; i++)
    ans = max(ans, dp[n - 1][i]);
  if (ans == -inf)
    fout << "Imposibil";
  else
    fout << ans;
  return 0;
}
