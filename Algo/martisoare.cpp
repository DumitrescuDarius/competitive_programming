#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("martisoare.in");
ofstream fout("martisoare.out");
int main() {
  int n, a, b, C, k = 0;
  a = b = 0;
  fin >> n;
  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    if (k == 0) {
      k = 1;
      C = x - i;
    } else {
      if (C == x - i)
        k++;
      else
        k--;
    }
    v.push_back(x);
  }
  int ans = 0;
  for (int i = 0; i < v.size(); i++) {
    int target = C + i;
    if (target != v[i]) {
      int p = 1;
      while (p <= target) {
        if ((target / p) % 10 != (v[i] / p) % 10) {
          a = (target / p) % 10;
          b = (v[i] / p) % 10;
          v[i] = (v[i] / (p * 10) * 10 + (target / p) % 10) * p + v[i] % p;
        }
        p *= 10;
      }
    }
    ans = max(ans, v[i]);
  }
  if (a > b)
    swap(a, b);
  fout << a << " " << b << "\n";
  fout << ans;
  return 0;
}
