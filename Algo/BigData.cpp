// Shit code made by Darius and chatgpt
#include <bits/stdc++.h>
// what the fuck are these libraries
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <fstream>
#include <vector>
#define ll long long
using namespace __gnu_pbds;
using namespace std;
ifstream fin("bigdata.in");
ofstream fout("bigdata.out");
// chatgpt code
typedef tree<pair<string, ll>,       // value + unique id to allow duplicates
             null_type,               // mapped type (none for set)
             less<pair<string, ll>>, // comparator
             rb_tree_tag,             // Red-Black Tree
             tree_order_statistics_node_update // policy for k-th element
             >
    ordered_multiset;
signed main() {

  // stupid unnoredered multiset cause normal erase slow af
  // nvm, it does not work
  // this shit works tho
  ordered_multiset mst;
  vector<pair<ll, ll>> query;
  ll n, q;
  fin >> n >> q;
  for (ll i = 0; i < q; i++) {
    ll a, b;
    fin >> a >> b;
    query.push_back({a, b});
  }
  for (ll i = 0; i < n; i++) {
    string s;
    fin >> s;
    mst.insert({s, i});
  }
  // comeone sempai, let's wsolve this problem, just erase those little fuckers
  for (ll i = 0; i < query.size(); i++) {
    if (query[i].first == 1) {
      auto it = mst.find_by_order(query[i].second - 1);
      // fuck this bs 1 indexing
      mst.erase(it);
    } else {
      auto it = mst.find_by_order(query[i].second - 1);
      //  why the fuck I get core dumped
      fout << it->first << "\n";
      // I want to kms
    }
  }
  // this shit dumb
  return 0;
}
