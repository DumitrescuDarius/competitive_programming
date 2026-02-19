#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("rmq.in");
ofstream fout("rmq.out");

vector<vector<int>> st;

void build(int n) {
  for (int k = 1; (1 << k) <= n; k++) {
    for (int i = 0; i + (1 << k) - 1 <= n; i++) {
      st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
  }
}

int query(int L, int R) {
  int len = R - L + 1;
  int k = floor(log2(len));
  return min(st[k][L], st[k][R - (1 << k) + 1]);
}

int main() {
  int n, q;
  fin >> n >> q;
  st.resize(30, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; i++) {
    fin >> st[0][i];
  }

  build(n);

  for (int i = 0; i < q; i++) {
    int L, R;
    fin >> L >> R;
    fout << query(L, R) << "\n";
  }
  return 0;
}
