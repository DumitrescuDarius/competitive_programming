#include <bits/stdc++.h>
#include <cmath>
#include <vector>
using namespace std;

vector<vector<int>> st;

void build(int n) {
  for (int k = 1; (1 << k) <= n; k++) {
    for (int i = 1; i + (1 << k) <= n; i++) {
      st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
  }
}

int query(int L, int R) {
  int len = R - L + 1;
  int k = floor(log2(len));
  return min(st[k][L], st[k][R - (1 << k) + 1]);
}

int main() {}
