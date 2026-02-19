#include <bits/stdc++.h>
#include <ios>
#include <vector>
using namespace std;
vector<int> tree;
int n;
// void update(int pos, int val) {
//   while (pos >= 1) {
//     tree[pos] += val;
//     pos -= (pos & -pos);
//   }
// }
//
// int query(int pos) {
//   int q = 0;
//   while (pos <= 32) {
//     q += tree[pos];
//     pos += (pos & -pos);
//   }
//   return q;
// }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> n;
  cin >> s;
  s.insert(s.begin(), 0);
  vector<vector<int>> dp(n + 1, vector<int>(33, 0));
  tree.resize(33, 0);

  for (int i = 1; i <= n; i++) {
    int val = s[i] - 'a' + 1;
    for (int j = 1; j <= 32; j++)
      dp[i][j] = dp[i - 1][j] + (j > val);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 32; j++) {
      cout << dp[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
