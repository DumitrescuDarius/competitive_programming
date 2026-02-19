
// Code by Patcas Csaba
// Time complexity: O(n * k)
// Space complexity: O(n * k)
// Method: DP
// Implementation time: 30 minutes

#include <bitset>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>

using namespace std;

#define LL long long
#define PII pair<int, int>
#define VB vector<bool>
#define VI vector<int>
#define VD vector<double>
#define VS vector<string>
#define VPII vector<pair<int, int>>
#define VVI vector<VI>
#define VVB vector<VB>

#define FORN(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORI(it, X)                                                            \
  for (__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define REPEAT do {
#define UNTIL(x)                                                               \
  }                                                                            \
  while (!(x))                                                                 \
    ;

#define SZ size()
#define BG begin()
#define EN end()
#define CL clear()
#define X first
#define Y second
#define RS resize
#define PB push_back
#define MP make_pair
#define ALL(x) x.begin(), x.end()

#define IN_FILE "joc.in"
#define OUT_FILE "joc.out"
ifstream fin(IN_FILE);
ofstream fout(OUT_FILE);

#define INF 10000001

int n, k;
VVI a;
vector<VVI> dp;

int Solve() {
  dp.RS(3, VVI(n + 1, VI(k + 1)));
  dp[1][1][1] = a[1][1];
  dp[2][1][1] = a[1][1] + a[2][1];
  FOR(j, 2, n) {
    FOR(i, 1, 2)
    FOR(q, 2, k) {
      if (q > j)
        break;
      dp[i][j][q] = dp[i][j - 1][q - 1] + a[i][j];
    }
    FOR(i, 1, 2) {
      int maxVal = -INF;
      FOR(q, 2, k) {
        if (q > j)
          break;
        maxVal = max(maxVal, dp[3 - i][j][q]);
      }
      dp[i][j][1] = maxVal + a[i][j];
    }
  }
  int ans = -INF;
  FOR(q, 1, k) ans = max(ans, dp[2][n][q]);
  return ans;
}

int main() {
  // Read data
  fin >> n >> k;
  a.RS(3, VI(n + 1));
  FOR(i, 1, n) fin >> a[1][i];
  FOR(i, 1, n) fin >> a[2][i];
  fin.close();

  // Write data
  fout << Solve();
  fout.close();

  return 0;
}
