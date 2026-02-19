#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("teamwork.in");
ofstream fout("teamwork.out");
int main() {
  int n;
  fin >> n;
  vector<vector<int>> mat(n, vector<int>(n, 0));
  vector<int> dp(1 << n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> mat[i][j];
    }
  }
  for (int mask = 0; mask < (1 << n); mask++) {
    int nb = __builtin_popcount(mask);
    for (int j = 0; j < n; j++) {
      if (!(mask & (1 << j)))
    }
  }
}

//
//    1   2   3   4   5   6   7   8   9   10
// 1   1   1   2
// 2   1   2   2
// 3
// 4
//
