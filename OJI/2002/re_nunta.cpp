#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("nunta.in");
ofstream fout("nunta.out");
int main() {
  int n;
  fin >> n;
  vector<int> v(n + 1);
  vector<vector<set<int>>> dp(n + 1, vector<set<int>>(n + 1));
  for (int i = 1; i <= n; i++) {
    fin >> v[i];
    dp[i][i].insert(v[i]);
  }

  for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      for (int k = l; k < r; k++) {
        for (int a : dp[l][k]) {
          for (int b : dp[k + 1][r]) {
            dp[l][r].insert(abs(a - b));
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << "(";
      for (auto it : dp[i][j])
        cout << it << " ";
      cout << ")";
    }
    cout << "\n";
  }

  fout << dp[1][n].size() << "\n";
  for (auto it : dp[1][n])
    fout << it << " ";

  return 0;
}

//  1 4 3 6 6
//
//  1 3 (0, 2) (6, 4, 3, 1) ()
//    4 1 (3, 5) (1, 3)
//      3 3 (3)
//        6 0
//          6
//
//
