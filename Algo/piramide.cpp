#include <bits/stdc++.h>
#include <fstream>
using namespace std;
ifstream fin("piramide.in");
ofstream fout("piramide.out");
int main() {
  int n, x, k, card = 0, ans = 0, index = 0, best = 0, pos = 0;
  int base = 2, total = 0;
  fin >> n >> x >> k;
  fin >> card;
  while (total + (base * (base + 1) / 2) <= n) {
    int cnt = 0;
    index++;
    total += (base * (base + 1) / 2);
    while (card <= total) {
      cnt++;
      if (!(fin >> card))
        break;
    }
    if (cnt > best) {
      best = cnt;
      pos = index;
    }
    base++;
    if (total >= x && ans == 0)
      ans = index;
  }
  fout << ans << "\n";
  fout << index << "\n";
  fout << n - total << "\n";
  fout << pos;
  return 0;
}
