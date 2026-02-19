#include <bits/stdc++.h>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;
ifstream fin("numar.in");
ofstream fout("numar.out");
int main() {
  int n, k;
  fin >> n >> k;
  set<int> st;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    v[i] = x;
  }
  int index = 0;
  int ans = 0;
  for (auto it : v) {
    if (st.empty())
      for (int i = 1; i <= k; i++)
        st.insert(i * it);
    else {
      int maxVal = *prev(st.end());
      for (auto i = 1; i <= k; i++) {
        if (i * it > maxVal)
          break;
        st.insert(i * it);
        if (st.size() > k)
          st.erase(prev(st.end()));
      }
    }
  }

  fout << *prev(st.end());
  return 0;
}
