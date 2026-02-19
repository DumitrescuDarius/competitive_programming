#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("birocratie.in");
ofstream fout("birocratie.out");
const int inf = 1e9 + 7;
int n;

bool inBounds(int x, int y) {
  if (x >= 1 && x <= n && y >= 1 && y <= n)
    return 1;
  return 0;
}

int main() {
  fin >> n;
  vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = 0; i <= n; i++) {
    dp[0][i] = -inf;
    dp[i][0] = -inf;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> mat[i][j];
  dp[1][1] = mat[1][1];
  for (int i = 2; i <= 2 * n; i++) {
    vector<pair<int, int>> cells;
    vector<int> exit1, exit2;
    for (int j = 1; j <= n; j++) {
      int x = j;
      int y = i - j + 1;
      if (y == 0)
        break;
      if (inBounds(x, y))
        cells.push_back({x, y});
    }
    for (auto &[x, y] : cells) {
      if (inBounds(x, y)) {
        int base = max(dp[x - 1][y], dp[x][y - 1]);
        if (exit1.empty())
          exit1.push_back(base + mat[x][y]);
        else
          exit1.push_back(max(exit1.back(), base) + mat[x][y]);
      }
    }
    for (int j = cells.size() - 1; j >= 0; j--) {
      int x = cells[j].first;
      int y = cells[j].second;
      if (inBounds(x, y)) {
        int base = max(dp[x - 1][y], dp[x][y - 1]);
        if (exit2.empty())
          exit2.push_back(base + mat[x][y]);
        else
          exit2.push_back(max(exit2.back(), base) + mat[x][y]);
      }
    }
    reverse(exit1.begin(), exit1.end());
    for (auto &[x, y] : cells) {
      if (inBounds(x, y)) {
        dp[x][y] = max(exit1.back(), exit2.back());
        exit1.pop_back();
        exit2.pop_back();
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cout << dp[i][j] << " ";
    cout << "\n";
  }
  fout << dp[n][n];
  return 0;
}

//
//
// pentru fiecare diagonala sec
//    exit 1 pentru valori de sus in jos
//    exit 2 pentru valori de jos in sus
//
//    o parcurg de sus in jos
//
//
//
//  1
//  1   2
//  1   2   3
//  1   2   3   4
//      1   2   3
//          1   2
//              1
//
//
//  for(int i = 1; i <= n; i ++)
//    for(int j = 0; j < n; j ++)
//      cin >> mat[i][i + j];
//
//
//
//  1
//  0   0
//  3   6   9
// 10   9   7
// parcurgere rand stanga - dreapta (r[], randAnterior[]) -> dp[];
//    parcurgere r[] unde r[index] = max(randAnterior[index], randAnterior[index
//    - 1]) + r[index];
//
// parcurgere dp stanga - drepta (dp[], r[]) -> leftRight[]
//    parcurgere dp[] unde dp[index] = max(dp[index - 1] + r[index], dp[index]);
//
// parcurgere dp dreapta - stanga (dp[], r[]) -> rightLeft[]
//    parcurgere dp[] unde dp[index] = max(dp[index + 1] + r[index], dp[index]);
//
// gasire maxim pentru fieacre index(leftRight[], rightLeft[]) -> ans[]
//    parecurgere ans[] unde ans[index] = max(leftRight[index],
//    rightLeft[index]);
//
// randAnterior = ans
//
