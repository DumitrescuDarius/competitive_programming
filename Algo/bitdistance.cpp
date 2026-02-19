#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {

  ll n;
  int ans = 0;
  cin >> n;
  while ((n & 1) == 0)
    n = n >> 1;
  while (n) {
    n = n >> 1;
    ans++;
  }
  cout << ans;
  return 0;
}
