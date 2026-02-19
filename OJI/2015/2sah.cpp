#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("2sah.in");
ofstream fout("2sah.out");
const int MOD = 100003;

vector<vector<int>> matrixMult(vector<vector<int>> &matrix1,
                               vector<vector<int>> &matrix2) {
  int n = matrix1.size();
  vector<vector<int>> ans(n, vector<int>(n));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        ans[i][j] = (ans[i][j] + matrix1[i][k] * matrix2[k][j]) % MOD;
  return ans;
}

vector<vector<int>> matrixPower(vector<vector<int>> matrix, int exp) {
  int n = matrix.size();
  vector<vector<int>> ans(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    ans[i][i] = 1;
  while (exp > 0) {
    if (exp % 2 == 1)
      ans = matrixMult(ans, matrix);
    matrix = matrixMult(matrix, matrix);
    exp >>= 1;
  }
  return ans;
}

int power(int base, int exp) {
  int ans = 1;
  while (exp > 0) {
    if (exp % 2 == 1)
      ans = (ans * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return ans;
}

signed main() {
  int cases, n, k;
  fin >> cases >> n >> k;
  if (cases == 1)
    fout << power(3, k - 1);
  if (cases == 2) {
    if (k > n + 1)
      fout << 0;
    else {
      // int target = n - k + 2;
      vector<vector<int>> matrix = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};
      vector<vector<int>> ans = matrixPower(matrix, n - k);
      int Tn = (ans[0][0] * 1LL + ans[0][1] * 1LL + ans[0][2] * 0LL) % MOD;
      fout << Tn;
    }
  }
  return 0;
}
