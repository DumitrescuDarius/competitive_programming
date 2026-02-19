#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("submultimi.in");
ofstream fout("submultimi.out");
vector<ll> perm;

ll main() {
  ll n, k = 1, p;
  fin >> n;
  p = pow(2, n);
  while (k <= p) {
    ll aux = k;
    ll index = 0;
    while (aux) {
      index++;
      if (aux & 1)
        fout << index << " ";
      aux >>= 1;
    }
    fout << "\n";
    k++;
  }
  return 0;
}
