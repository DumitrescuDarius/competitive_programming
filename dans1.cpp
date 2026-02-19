#include <bits/stdc++.h>
#include <fstream>
using namespace std;
ifstream fin("dans.in");
ofstream fout("dans.out");
const int nmax = 2 * (1e6 + 1);

bool isPrime[nmax];
void ciur() {
  isPrime[0] = 1;
  isPrime[1] = 1;
  for (int i = 2; i * i <= nmax; i++) {
    if (isPrime[i] == 0)
      for (int j = i * i; j <= nmax; j += i)
        isPrime[j] = 1;
  }
}

int main() {
  int c, n, d;
  ciur();
  fin >> c >> n >> d;
  if (c == 1) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      fin >> x;
      ans += (isPrime[x + d] == 0);
    }
    fout << ans;
  }
  if (c == 2) {
    int fr[10] = {};
    while (d) {
      fr[d % 10]++;
      d /= 10;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      fin >> x;
      bool ok = 1;
      while (x) {
        if (!fr[x % 10])
          ok = 0;
        x /= 10;
      }
      ans += ok;
    }
    fout << ans;
  }
}
