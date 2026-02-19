#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

vector<int> buildLPS(string &p) {
  vector<int> lps(p.size());
  for (int i = 1, j = 0; i < p.size();) {
    if (p[i] == p[j])
      lps[i++] = ++j;
    else if (j)
      j = lps[j - 1];
    else
      lps[i++] = 0;
  }
  return lps;
}

vector<int> kmp(string &p, string &t) {
  vector<int> lps = buildLPS(p);
  vector<int> ans;

  int i = 0, j = 0;
  while (j < t.size()) {
    if (p[i] == t[j]) {
      i++;
      j++;
    }

    if (i == p.size()) {
      ans.push_back(j - i);
      i = lps[i - 1];
    } else if (j < t.size() && p[i] != t[j]) {
      if (i)
        i = lps[i - 1];
      else
        j++;
    }
  }
  return ans;
}

int main() {
  string s1, s2;
  vector<int> ans;
  fin >> s1 >> s2;
  ans = kmp(s1, s2);
  fout << ans.size() << "\n";
  for (int i = 0; i < min((int)ans.size(), 1000); i++)
    fout << ans[i] << " ";
  return 0;
}
