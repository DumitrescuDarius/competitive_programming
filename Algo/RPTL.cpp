#include <bits/stdc++.h>
#include <fstream>
#define int long long
using namespace std;
ifstream fin("lgput.in");
ofstream fout("lgput.out");
const int MOD = 1999999973;

int power(int base, int exp) {
  int ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % MOD;
    exp /= 2;
    base = (base * base) % MOD;
  }
  return ans;
}

signed main() {
  int base, exp;
  fin >> base >> exp;

  fout << power(base, exp);
  return 0;
}
