#include <bits/stdc++.h>
using namespace std;
int nrDiv(int x) {
  int i, ans = 0;
  for (i = 1; i * i < x; i++) {
    if (x % i == 0)
      ans += 2;
  }
  if (i * i == x)
    ans++;
  return ans;
}
int main() {
  const int inf = 2000000000;
  int ans = 0;
  for (int i = 2; i * i * i * i < 2000000000; i++) {
    if (nrDiv(i) == 2)
      ans++;
  }
  cout << ans;
  return 0;
}
