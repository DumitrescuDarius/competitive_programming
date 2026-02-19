#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
private:
  bool inBorders(ll x, ll y, vector<string> &pyramid) {
    if (y >= 0 && x <= y)
      return 1;
    return 0;
  }

  void generate(ll x, ll y, vector<string> &pyramid) {
    if (inBorders(x, y, pyramid) && inBorders(x + 1, y, pyramid) &&
        inBorders(x, y - 1, pyramid)) {
    }
  }

public:
  bool pyramidTransition(string bottom, vector<string> &allowed) {
    vector<string> pyramid(bottom.size());
    bool ans = 0;
    for (ll i = 0; i < pyramid.size() - 1; i++)
      pyramid.resize(i + 1, "!");
    pyramid.push_back(bottom);
    return ans;
  }
};
