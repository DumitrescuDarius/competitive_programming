#include <bits/stdc++.h>
#include <ios>
#include <vector>
using namespace std;
int C;
void solve() {
  int n, cnt = 0;
  cin >> n;
  vector<string> mat;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    mat.push_back(s);
  }
  if (C == 1) {
    bool ans = 1;
    for (int i = 0; i < n; i++) {
      int cnt = 0;
      for (int j = 0; j < n; j++)
        cnt += (mat[i][j] == '1');
      if (cnt != n / 2)
        ans = 0;
    }
    for (int i = 0; i < n; i++) {
      int cnt = 0;
      for (int j = 0; j < n; j++)
        cnt += (mat[j][i] == '1');
      if (cnt != n / 2)
        ans = 0;
    }
    cout << ans;
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> C >> T;
  while (T--) {
    solve();
    cout << '\n';
  }
  return 0;
}
