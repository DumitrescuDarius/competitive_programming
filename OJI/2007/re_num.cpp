#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("numere.in");
ofstream fout("numere.out");
const int MOD = 9973;
signed main() {
  int n, k;
  fin >> n >> k;

  vector<int> div;
  set<int> fulDiv;
  // vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
  vector<int> prev(k + 1, 0);

  for (int i = 2; i <= min(k, 9LL); i++)
    if (k % i == 0)
      div.push_back(i);
  for (int i = 1; i * i <= k; i++)
    if (k % i == 0) {
      fulDiv.insert(i);
      fulDiv.insert(k / i);
    }

  prev[1] = 1;
  for (int i = 1; i <= n; i++) {
    vector<int> cur(k + 1, 0);
    for (auto j : fulDiv) {
      cur[j] = prev[j];
      for (auto it : div) {
        if (j % it == 0)
          cur[j] = (cur[j] + prev[j / it]) % MOD;
      }
    }
    prev = cur;
  }

  fout << prev[k];
  return 0;
}
