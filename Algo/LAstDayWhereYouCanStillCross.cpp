#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
private:
  vector<vector<ll>> delta = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  bool inBounds(ll x, ll y, vector<vector<ll>> &matrix) {
    if (x > 0 && x < matrix.size() && y > 0 && y < matrix[0].size())
      return true;
    return false;
  }

  void bfs(pair<ll, ll> node, ll type, vector<vector<ll>> &matrix) {
    queue<pair<ll, ll>> q;
    q.push({node.first, node.second});
    matrix[node.first][node.second] = type;
    while (!q.empty()) {
      pair<ll, ll> curr = q.front();
      q.pop();
      for (auto it : delta) {
        ll dx = curr.first + it[0];
        ll dy = curr.second + it[1];
        if (inBounds(dx, dy, matrix) && matrix[dx][dy] != 0 &&
            matrix[dx][dy] != type) {
          q.push({dx, dy});
          matrix[dx][dy] = type;
        }
      }
    }
  }

public:
  ll latestDayToCross(ll row, ll col, vector<vector<ll>> &cells) {
    vector<vector<ll>> matrix(row + 1, vector<ll>(col + 1, 1));
    cells.insert(cells.begin(), {0, 0});
    ll index = 0;
    for (auto it : cells) {
      matrix[it[0]][it[1]] = 0;
      for (ll i = 1; i <= col; i++)
        if (matrix[1][i] != 0 && matrix[1][i] != index)
          bfs({1, i}, index, matrix);
      bool ok = 0;
      for (ll i = 1; i <= col; i++)
        if (matrix[row][i] == index)
          ok = 1;
      if (!ok)
        break;
      index++;
    }
    return index;
  }
};
