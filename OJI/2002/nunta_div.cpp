#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("nunta.in");
ofstream fout("nunta.out");
vector<int> v;

map<pair<int, int>, set<int>> mp;

set<int> rec(int left, int right) {
  set<int> st;
  if (left == right) {
    st.insert(v[left]);
    return st;
  }
  if (mp.count({left, right}))
    return mp[{left, right}];
  for (int i = left; i < right; i++) {
    set<int> lt = rec(left, i);
    set<int> rt = rec(i + 1, right);
    for (auto it : lt) {
      for (auto jt : rt) {
        st.insert(abs(it - jt));
      }
    }
  }
  mp[{left, right}] = st;
  return st;
}

int main() {
  int n;
  fin >> n;
  v.resize(n + 1, 0);
  for (int i = 1; i <= n; i++)
    fin >> v[i];

  set<int> ans = rec(1, n);

  fout << ans.size() << "\n";
  for (auto it : ans)
    fout << it << " ";
  return 0;
}
