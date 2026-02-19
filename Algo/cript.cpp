#include <bits/stdc++.h>
#include <vector>
using namespace std;
ifstream fin("cript.in");
ofstream fout("cript.out");
ll main() {
  ll cases;
  fin >> cases;
  if (cases == 1) {
    string s;
    fin >> s;
    for (ll i = 0; i < s.size(); i++) {
      ll ch = (ll)s[i], init = ch;
      ll index = 0;
      vector<ll> bits;
      for (ll i = 0; i < 8; i++) {
        ll firstBit = (ch >> 7) & 1;
        bits.push_back(ch);
        cout << (ll)ch << "\n";
        if (firstBit)
          ch ^= (1 << 7);
        ch <<= 1;
        ch |= firstBit;
      }
      sort(bits.begin(), bits.end());
      ll maxVal = bits.back();
      for (ll j = 0; j < bits.size(); j++) {
        if (bits[j] == init) {
          index = j;
          break;
        }
      }
      for (ll i = 0; i < bits.size(); i++)
        fout << (bits[i] & 1);
      fout << index;
    }
  }
}
