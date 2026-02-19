#include <bits/stdc++.h>
#include <fstream>
using namespace std;
ifstream fin("partit.in");
ofstream fout("partit.out");
int mult2(int k) {
  if (k >= 0)
    return 1 << k;
  return 1;
}
int main() {
  int cases, n;
  fin >> cases >> n;
  if (cases == 1) {
    int k;
    fin >> k;
    int p = n - 2;
    int ans = 1;
    while (k - mult2(p) > 0) {
      k -= mult2(p);
      p--;
      ans++;
    }
    cout << ans;
  }
}
