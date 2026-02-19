#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#define int long long
using namespace std;
ifstream fin("aur.in");
ofstream fout("aur.out");
signed main() {
  int T, n;
  fin >> T >> n;
  if (T == 1) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      fin >> x;
      ans += floor(log10(x) + 1);
    }
    fout << ans;
  }
  if (T == 2) {
    int target, index = 0;
    fin >> target;
    for (int i = 0; i < n; i++) {
      int x;
      fin >> x;
      int p = 1;
      while (p * 10 <= x)
        p *= 10;
      while (p) {
        cout << (x / p) % 10 << " ";
        index++;
        if (index == target) {
          fout << (x / p) % 10;
          return 0;
        }
        p /= 10;
      }
    }
  }
  if (T == 3) {
    int target, part = 0, ans = 0;
    fin >> target;
    int mod = 1;
    for (int i = 0; i < target; i++)
      mod *= 10;
    for (int i = 0; i < n; i++) {
      int x;
      fin >> x;
      int p = 1;
      while (p * 10 <= x)
        p *= 10;
      while (p) {
        int digit = (x / p) % 10;
        part = (part * 10 + digit) % mod;
        ans = max(ans, part);
        p /= 10;
      }
    }
    fout << ans;
  }
  return 0;
}
