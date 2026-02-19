#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("birocratie.in");
ofstream fout("birocratie.out");
const int inf = 1e9 + 7;
int n;

void calcDir(int start, int finish, vector<int> &cur, int dir,
             vector<int> &prev, vector<int> &ans) {

  vector<int> calc(n + 2, -inf);

  int i = start;
  calc[i] = max(prev[i - 1], prev[i]) + cur[i];

  for (i = start + dir; i != finish + dir; i += dir) {
    int dp = max(prev[i - 1], prev[i]);
    calc[i] = max(calc[i - dir], dp) + cur[i];
    ans[i] = max(ans[i], calc[i]);
  }
}

int main() {
  fin >> n;
  vector<vector<int>> mat(2 * n + 1, vector<int>(2 * n + 1, 0));
  vector<int> prev(n + 2, -inf);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> mat[i + j - 1][j];

  prev[1] = mat[1][1];

  for (int i = 2; i < 2 * n; i++) {
    int start, finish;
    if (i <= n) {
      start = 1;
      finish = i;
    } else {
      start = i - n + 1;
      finish = n;
    }
    vector<int> ans(n + 1, -inf);

    calcDir(finish, start, mat[i], -1, prev, ans);
    calcDir(finish, start, mat[i], -1, prev, ans);

    prev = ans;
  }

  fout << prev[n];

  return 0;
}
