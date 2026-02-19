#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("birocratie.in");
ofstream fout("birocratie.out");
const int inf = 1e9 + 7;
int n;
vector<int> findDps(vector<int> &prevDp, int start, int finish) {
  vector<int> dp(n + 2, -inf);
  for (int i = start; i <= finish; i++)
    dp[i] = max(prevDp[i - 1], prevDp[i]);
  return dp;
}

vector<int> pass(vector<int> &dp, vector<int> &line, int dir, int start,
                 int finish) {
  vector<int> p(n + 2, 0);
  for (int i = start; i != finish + dir; i += dir) {
    p[i] = max(p[i - dir] + line[i], dp[i] + line[i]);
  }
  return p;
}

int main() {
  fin >> n;
  vector<vector<int>> mat(2 * n + 1, vector<int>(2 * n + 1, -inf));
  vector<int> prevDp(n + 2, -inf);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> mat[i + j][j];
  prevDp[1] = mat[1][1];
  for (int i = 2; i <= 2 * n; i++) {
    int start, finish;
    if (i <= n)
      start = 1, finish = i;
    else
      start = i - n + 1, finish = n;
    vector<int> dp = findDps(prevDp, start, finish);

    vector<int> leftRight = pass(dp, mat[i], 1, start, finish);
    vector<int> rightLeft = pass(dp, mat[i], -1, finish, start);
    for (int j = start; j <= finish; j++)
      dp[j] = max(leftRight[j], rightLeft[j]);
    prevDp = dp;
  }
  fout << prevDp[n] << " \n";
}
