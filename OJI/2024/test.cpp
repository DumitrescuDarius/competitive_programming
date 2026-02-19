#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("birocratie.in");
int main() {
  int n;
  fin >> n;
  vector<vector<int>> mat(n * 2 + 2, vector<int>(n * 2 + 2, 0));

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> mat[i + j][j];
  for (int i = 1; i <= 2 * n; i++) {
    for (int j = 1; j <= n * 2; j++)
      cout << mat[i][j] << " ";
    cout << "\n";
  }
}
