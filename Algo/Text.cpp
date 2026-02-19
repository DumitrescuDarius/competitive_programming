#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("text.in");
ofstream fout("text.out");
int main() {
  string s;
  int maxVal = 0, cnt = 0;
  vector<int> fr(40, 0);
  vector<pair<string, int>> ss;
  char ch = 0;
  while (fin >> s) {
    fr[s.back() - 'a'] = max(fr[s.front() - 'a'] + 1, fr[s.back() - 'a']);
    if (fr[s.back() - 'a'] > maxVal) {
      maxVal = max(fr[s.back() - 'a'], maxVal);
      ch = s.back();
    }
    ss.push_back({s, fr[s.back() - 'a']});
    cnt++;
  }
  fout << cnt - maxVal << "\n";
  fout << cnt << "\n";
  vector<string> ans;
  for (int i = ss.size() - 1; i >= 0; i--) {
    s = ss[i].first;
    int val = ss[i].second;
    if (val == maxVal && s.back() == ch) {
      ch = s.front();
      ans.push_back(s);
      maxVal--;
    }
  }

  for (int i = ans.size() - 1; i >= 0; i--)
    fout << ans[i] << "\n";

  return 0;
}
