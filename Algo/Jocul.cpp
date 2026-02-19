#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("jocul.in");
ofstream fout("jocul.out");
const int nmax = 100001;
int main() {
  int n, target = 0;
  fin >> n;
  vector<vector<int>> dp(n + 1, vector<int>(nmax, 0));
  vector<int> nums(n + 1);
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    nums[i] = x;
    target += x;
  }

  for (int i = 1; i <= n; i++) {
    int x = nums[i];
    for (int j = 0; j < nmax; j++) {
      dp[i][j + x] += dp[i - 1][j];
      dp[i][j] += dp[i - 1][j];
    }
    dp[i][x]++;
  }
}
