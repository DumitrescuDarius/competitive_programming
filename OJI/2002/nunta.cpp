
#include <bits/stdc++.h>
#include <fstream>
#include <unordered_set>
#include <vector>
using namespace std;
ifstream fin("nunta.in");
ofstream fout("nunta.out");

int main() {
  int n;
  fin >> n;
  vector<vector<unordered_set<int>>> dp(n + 1,
                                        vector<unordered_set<int>>(n + 1));
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    fin >> v[i];
    dp[i][i].insert(v[i]);
  }

  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len - 1 < n; i++) {
      int j = i + len - 1;

      unordered_set<int> cur;

      for (int k = i; k < j; k++) {
        for (int x : dp[i][k]) {
          for (int y : dp[k + 1][j])
            cur.insert(abs(x - y));
        }
      }

      dp[i][j] = std::move(cur);
    }
  }

  vector<int> ans(dp[0][n - 1].begin(), dp[0][n - 1].end());
  sort(ans.begin(), ans.end());

  fout << ans.size() << "\n";
  for (auto it : ans)
    fout << it << " ";

  return 0;
}
