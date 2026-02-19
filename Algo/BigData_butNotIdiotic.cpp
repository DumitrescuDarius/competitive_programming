// An attrocity of a code by Darius Dumitrescu
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("bigdata.in");
ofstream fout("bigdata.out");
ll n;

// update the freddy fazbear tree
void update(ll pos, ll val, vector<ll> &tree) {
  while (pos <= n) {
    tree[pos] += val;
    pos += pos & -pos;
  }
}

// ask mr freddy fazbear for the pos element
ll query(ll pos, vector<ll> &tree) {
  ll sum = 0;
  while (pos > 0) {
    sum += tree[pos];
    pos -= pos & -pos;
  }
  return sum;
}

ll main() {
  ll q;
  vector<pair<ll, ll>> querries; // querries of queries, idk how to type
                                   // also why tf do you give me the
                                   // elements of v after the querries

  fin >> n >> q;
  vector<ll> tree(n + 1, 0); // freddy fazbear tree
  vector<string> ss(n + 1, 0);
  for (ll i = 0; i < q; i++) {
    ll type, pos;
    fin >> type >> pos;
    querries.push_back({type, pos});
  }
  for (ll i = 1; i <= n; i++) {
    string s;
    fin >> s;
    ss[i] = s;
  }
  // plesae mr freddy fix my code

  for (auto it : querries) {
    ll type = it.first;
    ll pos = it.second;
    if (type == 1) {
      update(pos, -1, tree); // please mr freddy update my tree
    } else {
      fout << ss[pos + query(pos, tree)] << "\n";
      // please fazbear gimme 100 p
    }
  }
  // plese please plesepla pleplwplpaplespl gimme 100 p
  return 0;
}
