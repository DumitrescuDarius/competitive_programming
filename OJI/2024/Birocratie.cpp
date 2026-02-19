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
  vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -inf));

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> matrix[i][j];

  dp[1][1] = matrix[1][1];

  for (int i = 2; i <= 2 * n - 1; i++) {
    int len, left, right;
    if (i <= n) {
      len = i;
      left = len;
      right = 1;
    } else {
      len = 2 * n - len;
      left = n;
      right = len - n + 1;
    }

    vector<int> base;
    base.resize(len + 1, -inf);
    cout << left << " " << right << "\n";

    for (int k = 1; k <= len; k++) {
      int x = left - k + 1;
      int y = i - x + 1;
      cout << x << " " << y << "\n";
      if (inBounds(x, t))
    }
  }

  return 0;
}
