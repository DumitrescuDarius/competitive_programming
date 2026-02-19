#include <bits/stdc++.h>
#include <vector>
using namespace std;
ifstream fin("bilbob.in");
ofstream fout("bilbob.out");
ll main() {
  ll n, m;
  fin >> n >> m;
  vector<vector<ll>> dp(n + 2, vector<ll>(m + 2, 0));
  for (ll i = 1; i <= n; i++)
    for (ll j = 1; j <= m; j++) {
      ll x;
      if (j >= i)
        fin >> dp[i][j];
      else
        fin >> x;
    }

  for (ll j = 1; j <= m; j++)
    for (ll i = 1; i <= n; i++)
      dp[i][j] += max(max(dp[i - 1][j - 1], dp[i][j - 1]), dp[i + 1][j - 1]);
  for (ll i = 1; i <= n; i++) {
    for (ll j = 1; j <= m; j++)
      cout << dp[i][j] << " ";
    cout << "\n";
  }
  fout << dp[1][m];
  return 0;
}
