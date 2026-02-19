#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("birocratie.in");
ofstream fout("birocratie.out");
const int inf = 1e9 + 7;
int main() {
  int n;
  fin >> n;
  vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> mat[i][j];
  for (int i = 0; i <= n; i++) {
    dp[i][0] = -inf;
    dp[0][i] = -inf;
  }
  dp[1][1] = mat[1][1];
  for (int i = 3; i <= 2 * n; i++) {
    int s = n - abs(i - 1 - n);
    vector<int> exit1, exit2;
    for (int j = 1; j <= s; j++) {
      int x = j;
      if (i > n + 1)
        x = j + i - n - 1;
      else
        x = j;
      int y = i - x;
      cout << x << " " << y << "\n";
      dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]) + mat[x][y];
      if (j == 1)
        exit1.push_back(dp[x][y]);
      else
        exit1.push_back(max(exit1.back() + mat[x][y], dp[x][y]));
    }
    for (int j = s; j >= 1; j--) {
      int x = j;
      if (i > n + 1)
        x = j + i - n - 1;
      else
        x = j;
      int y = i - x;
      if (j == s)
        exit2.push_back(dp[x][y]);
      else
        exit2.push_back(max(exit2.back() + mat[x][y], dp[x][y]));
    }
    reverse(exit2.begin(), exit2.end());
    for (int j = 1; j <= s; j++) {
      int x = j;
      if (i > n + 1)
        x = j + i - n - 1;
      else
        x = j;
      int y = i - x;
      dp[x][y] = max(exit1[j - 1], exit2[j - 1]);
    }
  }
  fout << dp[n][n];
  return 0;
}
