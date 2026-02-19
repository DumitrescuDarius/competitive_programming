#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("numere.in");
ofstream fout("numere.out");
const int MOD = 9973;
int n, m, ans;

long long modPow(long long a, long long e) {
  long long r = 1;
  while (e) {
    if (e & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }
  return r;
}

long long modInv(long long x) { return modPow(x, MOD - 2); }

long long comb(int total, int take) {
  long long C = 1, div = 1;
  for (int i = 1; i <= take; i++) {
    C = C * (total - i + 1) % MOD;
    div = div * i % MOD;
  }
  return C * modInv(div) % MOD;
}

void calcComb(vector<int> &v) {

  int len = v.size(), k = 0;
  int C = 1;
  vector<int> tr;
  tr.push_back(1);
  for (int i = 1; i < len; i++) {
    if (v[i] == v[i - 1])
      tr[k]++;
    else {
      k++;
      tr.push_back(1);
    }
  }
  for (auto it : tr) {
    C = C * comb(len, it);
    len -= it;
  }
  ans = (ans + C) % MOD;
}

void findPos(int pos, int prod, vector<int> v) {
  if (prod == m) {
    calcComb(v);
    return;
  }
  if (pos >= n)
    return;
  int start = 9;
  if (pos > 0)
    start = v[pos - 1];
  for (int i = start; i > 1; i--) {
    v[pos] = i;
    if (prod * i <= m)
      findPos(pos + 1, prod * i, v);
  }
}

signed main() {
  fin >> n >> m;
  vector<int> v(n, 1);

  findPos(0, 1, v);

  fout << ans;
  return 0;
}
