#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("elmaj.in");
ofstream fout("elmaj.out");
int main() {
  int n;
  fin >> n;
  int cnt = 0, val;
  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    v.push_back(x);
    if (cnt == 0) {
      cnt++;
      val = x;
    } else if (val != x)
      cnt--;
    else
      cnt++;
  }
  cnt = 0;
  for (int i = 0; i < v.size(); i++)
    if (v[i] == val)
      cnt++;
  fout << val << " " << cnt;
  return 0;
}
