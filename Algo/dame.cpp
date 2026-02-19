#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("damesah.in");
ofstream fout("damesah.out");
int n, ans;
bool ok;
vector<int> fr;
bool valid(vector<int> &perm) {
  int index = 0;
  for (int i = perm.size() - 2; i >= 0; i--) {
    index++;
    if (perm[i] + index == perm.back() || perm[i] - index == perm.back() ||
        perm[i] == perm.back())
      return 0;
  }
  return 1;
}

void print(vector<int> &perm) {
  if (!ok) {
    ok ^= 1;
    for (auto it : perm)
      fout << it << " ";
    fout << "\n";
  }
  ans++;
}

void gen(vector<int> &perm) {
  if (perm.size() < n) {
    for (int i = 1; i <= n; i++) {
      if (fr[i] == 1)
        continue;
      fr[i] ^= 1;
      perm.push_back(i);
      if (valid(perm))
        gen(perm);
      perm.pop_back();
      fr[i] ^= 1;
    }
  } else
    print(perm);
}
int main() {
  fin >> n;
  fr.assign(n + 1, 0);
  vector<int> perm;
  gen(perm);
  fout << ans;
  return 0;
}
