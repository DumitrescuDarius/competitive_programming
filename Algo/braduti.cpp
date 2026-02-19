#include <bits/stdc++.h>
#include <fstream>
#define int long long
using namespace std;
ifstream fin("braduti.in");
ofstream fout("braduti.out");
int fact[23];

void genFactorials() {
  fact[0] = 1;
  for (int i = 1; i < 23; i++)
    fact[i] = fact[i - 1] * i;
}

int comb(int a, int b) { return fact[a] / (fact[b] * fact[a - b]); }

signed main() {
  genFactorials();
  int n, cases;
  fin >> cases >> n;
  if (cases == 1) {
    int k = 3, ans = 0;
    while (n - k >= 0) {
      n -= k;
      k += 2;
      ans++;
    }
    fout << ans;
    return 0;
  }
  if (cases == 2) {
    int k = 1, ans = 1;
    while (n - k > 0) {
      k += 2;
      ans *= comb(n, k);
      n -= k;
    }
    fout << ans;
  }
}
