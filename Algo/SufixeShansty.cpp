#include <bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;

bool isSquare(int nr) {
  if (nr == 0)
    return 0;
  int sq = sqrt(nr);
  if (sq * sq == nr)
    return 1;
  return 0;
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, cnt = 0;
    cin >> x;
    for (int p = 10; p <= x * 10; p *= 10) {
      int suf = x % p;
      if (isSquare(suf))
        cnt++;
    }
    cout << cnt << "\n";
  }
  return 0;
}
