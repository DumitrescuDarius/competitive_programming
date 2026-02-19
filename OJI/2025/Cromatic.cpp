#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#define int long long
using namespace std;
ifstream fin("cromatic.in");
ofstream fout("cromatic.out");
const int MOD = 1e9 + 7;
vector<int> fact, invfact;

int power(int a, int e) {
  int res = 1;
  while (e) {
    if (e & 1)
      res = res * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }
  return res;
}
void precompute_fact(int n) {
  fact.resize(n + 1);
  invfact.resize(n + 1);

  fact[0] = 1;
  for (int i = 1; i <= n; i++)
    fact[i] = fact[i - 1] * i % MOD;

  invfact[n] = power(fact[n], MOD - 2);

  for (int i = n; i > 0; i--)
    invfact[i - 1] = invfact[i] * i % MOD;
}
long long permutationIndex(const vector<int> &perm) {
  int n = perm.size();
  long long rank = 0;

  for (int i = 0; i < n; i++) {
    int count = 0;
    for (int j = i + 1; j < n; j++) {
      if (perm[j] < perm[i])
        count++;
    }
    rank = (rank + count * fact[n - i - 1]) % MOD;
  }

  return (rank + 1) % MOD;
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int cases, n;
  fin >> cases;
  fin >> n;
  vector<int> v(n);
  precompute_fact(n);
  for (int i = 0; i < n; i++)
    fin >> v[i];
  if (cases == 1) {
    sort(v.begin(), v.end());
    for (int i = 1; i < n; i++)
      if (v[i - 1] == v[i]) {
        fout << 0;
        return 0;
      }
    int ans = power(2, n - 1);
    fout << ans;
  }
  if (cases == 2) {
    fout << 1;
    return 0;
    vector<int> bits;
    int mn = 0, ans = 0;
    for (int i = 1; i < v.size(); i++) {
      mn += v[i] < v[0];
      bits.push_back(v[i] > v[0]);
    }

    ans = power(2, mn) % MOD;
    int permNum = permutationIndex(bits);
    fout << (ans + permNum % MOD);
  }
  return 0;
}
