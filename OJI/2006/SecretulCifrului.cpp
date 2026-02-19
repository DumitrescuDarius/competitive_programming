#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("cifru.in");
ofstream fout("cifru.out");
signed main() {
  const int MOD = 19997;
  int n, e;
  fin >> n >> e;
  vector<vector<int>> dp(n + 1);
  dp[1].push_back(1);
  int sum = 1;
  for (int i = 2; i <= n; i++) {
    int aux = sum;
    sum = 0;
    for (int j = 0; j < i; j++) {
      int val = (aux + j) % MOD;
      dp[i].push_back(val);
      sum = (sum + val) % MOD;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < dp[i].size(); j++)
      cout << dp[i][j] << " ";
    cout << "\n";
  }
}

// 1 : 1 2 : 1 2 3 : 3 4 5
//
//
// 1 3 2
// 2 3 1
// 3 2 1
//
// 1 2 3 4 5
// 4 3 5 2 1
//
// 1 2 3 4 5
// 5 4 2 1 3
//
// 1 2 3 4 5
// 5 4 2 1 3
//
// 1 2 3 4 5
// 5 4 2 1 3
