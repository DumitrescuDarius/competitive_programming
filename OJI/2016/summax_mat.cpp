#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("summax.in");
ofstream fout("summax.out");
const int bound = 2000000001;

vector<vector<pair<int, int>>> dp;
vector<int> perm;
int R;

void print() {
  for (int i = perm.size() - 1; i >= 0; i--)
    fout << perm[i] << " ";
  fout << "\n";
}

void dfs(int x, int y, int &target) {

  perm.push_back(y);
  if (x == 1) {
    print();
    perm.pop_back();
    if (target < R)
      target++;
    return;
  }
  if (dp[x - 1][y].first == dp[x - 1][y - 1].first) {
    if (target <= dp[x - 1][y - 1].second)
      dfs(x - 1, y - 1, target);
    target -= dp[x - 1][y - 1].second;
    dfs(x - 1, y, target);
    target += dp[x - 1][y - 1].second;
  }
  if (dp[x - 1][y].first > dp[x - 1][y - 1].first)
    dfs(x - 1, y, target);
  if (dp[x - 1][y].first < dp[x - 1][y - 1].first)
    dfs(x - 1, y - 1, target);
  perm.pop_back();
}

signed main() {
  int cases, n, left;
  fin >> cases;
  fin >> n >> left >> R;

  dp.resize(n + 1);

  int x;

  int maxVal = 0;

  fin >> x;

  dp[1].assign(3, {0, 0});
  dp[1][1] = {x, 1};

  for (int i = 2; i <= n; i++) {
    dp[i].assign(i + 2, {0, 0});
    for (int j = 1; j <= i; j++) {
      fin >> x;
      if (dp[i - 1][j].first == dp[i - 1][j - 1].first) {
        dp[i][j].first = dp[i - 1][j].first + x;
        dp[i][j].second =
            min(dp[i - 1][j].second + dp[i - 1][j - 1].second, bound);
      }
      if (dp[i - 1][j].first > dp[i - 1][j - 1].first) {
        dp[i][j].first = dp[i - 1][j].first + x;
        dp[i][j].second = dp[i - 1][j].second;
      }
      if (dp[i - 1][j].first < dp[i - 1][j - 1].first) {
        dp[i][j].first = dp[i - 1][j - 1].first + x;
        dp[i][j].second = dp[i - 1][j - 1].second;
      }
      if (i == n)
        maxVal = max(maxVal, dp[i][j].first);
    }
  }

  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j < dp[i].size() - 1; j++) {
  //     cout << dp[i][j].first << " ";
  //   }
  //   cout << "\n";
  // }

  if (cases == 1) {
    int ans = 0;

    for (int i = 1; i <= n; i++) {
      if (dp[n][i].first == maxVal)
        ans = min(ans + dp[n][i].second, bound);
    }
    fout << ans;
  } else {
    int x = n;
    int target = left;
    for (int i = 1; i <= n; i++) {
      if (dp[n][i].first == maxVal) {
        if (target > dp[n][i].second) {
          target -= dp[n][i].second;
          R -= dp[n][i].second;
        } else {
          dfs(n, i, target);
          break;
        }
      }
    }
  }
  return 0;
}
