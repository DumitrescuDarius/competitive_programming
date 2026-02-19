#include <bits/stdc++.h>
#include <iomanip>
#include <ios>
#include <vector>
using namespace std;

double s2(ll a, ll b) { return max(a, b) + (double)min(a, b) / 2; }

double s3(ll a, ll b, ll c) { return a + b + c - min(a, min(b, c)); }

ll main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  ll n;
  cin >> n;
  vector<ll> v(n + 1, 0);
  vector<double> dp(n + 1, 0);
  // I hate dp-s...
  for (ll i = 1; i <= n; i++) {
    ll x;
    cin >> x;
    v[i] = x;
  }
  dp[1] = v[1];
  for (ll i = 2; i <= n; i++) {
    if (i == 2)
      dp[i] = s2(v[i - 1], v[i]);
    else {
      double sum1 = dp[i - 1] + v[i];
      double sum2 = dp[i - 2] + s2(v[i - 1], v[i]);
      double sum3 = dp[i - 3] + s3(v[i - 2], v[i - 1], v[i]);
      dp[i] = min(sum1, min(sum2, sum3));
    }
  }
  cout << fixed << setprecision(1) << dp[n];
  return 0;
}
