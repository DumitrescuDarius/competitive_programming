#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
private:
  int n, m;
  bool inBounds(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= m)
      return 1;
    return 0;
  }

public:
  int maxSideLength(vector<vector<int>> &mat, int threshold) {
    n = mat.size();
    m = mat[0].size();
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        pref[i][j] = mat[i - 1][j - 1];
        pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int x = i, y = j;
        while (inBounds(x, y)) {
          int sum =
              pref[i][j] - pref[x - 1][j] - pref[i][y - 1] - pref[x - 1][y - 1];
          if (sum <= threshold)
            ans = max(ans, x - i + 1);
          x--;
          y--;
        }
      }
    }
    return ans;
  }
};
