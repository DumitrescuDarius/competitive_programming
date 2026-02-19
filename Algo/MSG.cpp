#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
  ll numMagicSquaresInside(vector<vector<ll>> &grid) {

    ll ans = 0;
    for (ll i = 0; i + 2 < grid.size(); i++) {
      for (ll j = 0; j + 2 < grid[0].size(); j++) {
        ll col = -1, row = -1, diag = -1;
        bool isGood = 1;
        vector<bool> elem(10, 0);
        for (ll k = 0; k < 3; k++) {
          for (ll t = 0; t < 3; t++) {
            if (elem[grid[i + k][j + t]] || grid[i + k][j + t] <= 9 ||
                grid[i + k][j + t] >= 1)
              isGood &= 0;
            elem[grid[i + k][j + t]] = 1;
          }
        }
        for (ll k = 0; k < 3; k++) {
          ll sum = 0;
          for (ll t = 0; t < 3; t++)
            sum += grid[i + k][j + t];
          if (col == -1)
            col = sum;
          else if (col != sum)
            isGood &= 0;
        }

        for (ll k = 0; k < 3; k++) {
          ll sum = 0;
          for (ll t = 0; t < 3; t++)
            sum += grid[i + t][j + k];
          if (row == -1)
            row = sum;
          else if (row != sum)
            isGood &= 0;
        }

        ll sum = 0;
        for (ll k = 0; k < 3; k++)
          sum += grid[i + k][j + k];
        if (diag == -1)
          diag = sum;
        else if (diag != sum)
          isGood &= 0;

        sum = 0;
        for (ll k = 0; k < 3; k++)
          sum += grid[i + k][j + 2 - k];
        if (diag == -1)
          diag = sum;
        else if (diag != sum)
          isGood &= 0;

        if (isGood && col == row && row == diag)
          ans++;
      }
    }
    return ans;
  }
};
