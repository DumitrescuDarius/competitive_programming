// Drosu se duce la magazinul crispy din curtea scolii cu K lei si are o
// probabilitate 1/2 sa aleaga unul dintre fiecare n sortimente de pui crispi
// (sau pateu). Fiecare pui crispy (sau pateu) are un pret V(i). Scrie cati bani
// cheltuieste drosu in medie (modulo 10007)
//
// stdin
// 5 10
// 2 4 1 5 3
//
// stdout
// 3506
//

#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int MOD = 10007;

int power(int base, int exp) {
  int ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % MOD;
    base = (base * base) % MOD;
    exp /= 2;
  }
  return ans;
}

int modInv(int n) { return power(n, MOD - 2); }

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> prev(k + 1, 0);
  prev[0] = 1;

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    vector<int> cur(k + 1, 0);
    for (int j = 0; j <= k; j++) {
      cur[j] += prev[j];
      if (j + x <= k)
        cur[j + x] += prev[j];
    }
    prev = cur;
  }

  int total = 0, div = 0;
  for (int i = 0; i <= k; i++) {
    total = (total + i * prev[i]) % MOD;
    div = (div + prev[i]) % MOD;
  }

  cout << (total * modInv(div)) % MOD;
  return 0;
}
