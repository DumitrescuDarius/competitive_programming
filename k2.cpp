#include <bits/stdc++.h>
#include <fstream>
#define int long long
using namespace std;
ifstream fin("k2.in");
ofstream fout("k2.out");

signed main() {
  int T, n;
  fin >> T >> n;
  if (T == 1) {
    int ans = sqrtl(n);
    fout << ans + 1;
  }
  if (T == 2) {
    int root = sqrtl(n);
    int prev_sq = root * root;
    if (n == prev_sq) {
      fout << 1;
    } else {
      int pos = n - prev_sq;
      int side = root + 1;
      if (pos < side)
        fout << pos;
      else
        fout << pos - side + 1;
    }
  }
}
