#include <bits/stdc++.h>
using namespace std;
ifstream fin("acoperire.in");
ofstream fout("acoperire.out");
int main() {
  int n;
  map<int, int> mp;
  fin >> n;
  for (int i = 0; i < n; i++) {
    double x, y;
    fin >> x >> y;
    double mid = (x + y) / 2;
    double len = (y - x) / 2;
    mp[mid] = len;
  }
  int q;
  fin >> q;
}
