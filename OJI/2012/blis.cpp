#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("blis.in");
ofstream fout("blis.out");
const int inf = 1e9 + 7;

int convertFromBinary(string &s) {
  int num = 0;
  for (auto it : s) {
    num *= 2;
    num += it - '0';
  }
  return num;
}

int main() {
  int k, ans = 0, maxVal = 0, len;
  string s;
  fin >> k >> s;
  len = s.size();

  string aux = s;
  for (int i = 0; i + k <= s.size(); i++) {
    string str;
    str.assign(s.begin() + i, s.begin() + i + k);
    ans = max(ans, convertFromBinary(str));
    aux.pop_back();
  }

  fout << ans << "\n";

  vector<vector<pair<int, int>>> dp(len,
                                    vector<pair<int, int>>(k + 1, {inf, 0}));

  for (int i = 0; i < len; i++) {
    for (int l = 1; l <= k && i - l + 1 >= 0; l++) {

      string str = s.substr(i - l + 1, l);
      int val = convertFromBinary(str);

      dp[i][l].first = val;
      dp[i][l].second = 1;
      for (int prevEnd = 0; prevEnd <= i - l; prevEnd++) {
        for (int prevLen = 1; prevLen <= k; prevLen++) {
          if (dp[prevEnd][prevLen].first < val) {
            dp[i][l].second =
                max(dp[i][l].second, dp[prevEnd][prevLen].second + 1);
          }
        }
      }
      maxVal = max(maxVal, dp[i][l].second);
    }
  }

  fout << maxVal;

  return 0;
}
