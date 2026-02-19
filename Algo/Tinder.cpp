#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  vector<int> dp(k + 1);
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    for (int j = k; j >= y; j--) {
      dp[j] = max(dp[j], dp[j - y] + x);
    }
  }
  cout << *max_element(dp.begin(), dp.end());
  return 0;
}
