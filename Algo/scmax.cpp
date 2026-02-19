#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
ifstream fin("scmax.in");
ofstream fout("scmax.out");
ll main() {
  ll n;
  vector<ll> c;
  fin >> n;
  for (ll i = 0; i < n; i++) {
    ll x;
    fin >> x;
    if (c.empty() || x > c.back())
      c.push_back(x);
    else {
      ll it = lower_bound(c.begin(), c.end(), x) - c.begin();
      c[it] = x;
    }
  }
  fout << c.size() << "\n";
  for (ll i = 0; i < c.size(); i++) {
    fout << c[i] << " ";
  }
}
