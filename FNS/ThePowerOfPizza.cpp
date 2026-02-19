#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, ans = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int S, F;
    bool P;
    cin >> S >> F >> P;
    if (P == 1)
      ans += (F - S) * 2;
    else
      ans += (F - S);
  }
  cout << ans;
  return 0;
}
