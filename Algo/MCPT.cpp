#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
class Solution {
private:
  const int inf = 1e9 + 7;
  int n, m;
  struct Node {
    int x, y, w, t;

    bool operator<(const Node &other) const { return other.w < w; }
  };

  vector<vector<int>> delta = {{1, 0}, {0, 1}};
  vector<vector<int>> globalGrid;

  bool inBounds(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m)
      return 1;
    return 0;
  }

  vector<vector<int>> findLesser(int val) {
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (globalGrid[i][j] <= val)
          ans.push_back({i, j});
    return ans;
  }

public:
  int minCost(vector<vector<int>> &grid, int k) {
    globalGrid = grid;
    n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, inf));
    vector<vector<int>> tel(n, vector<int>(m, -inf));

    priority_queue<Node> pq;

    pq.push({0, 0, 0, k});
    dist[0][0] = 0;
    tel[0][0] = k;
    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      int x = cur.x;
      int y = cur.y;
      int w = cur.w;
      int t = cur.t;
      // cout << x << " " << y << " " << w << "\n";
      // if (w > dist[x][y] && t <= tel[x][y])
      //   continue;
      vector<vector<int>> less = findLesser(grid[x][y]);
      for (auto it : delta) {
        int newX = x + it[0];
        int newY = y + it[1];
        if (!inBounds(newX, newY))
          continue;
        int newW = w + grid[newX][newY];
        int newT = t;
        if (newW < dist[newX][newY] || newT > tel[newX][newY]) {
          dist[newX][newY] = min(dist[newX][newY], newW);
          tel[newX][newY] = max(tel[newX][newY], newT);
          pq.push({newX, newY, newW, newT});
        }
      }
      for (auto it : less) {
        int newX = it[0];
        int newY = it[1];
        int newW = w;
        int newT = t - 1;
        if (newT < 0)
          continue;
        if (newW < dist[newX][newY] || newT > tel[newX][newY]) {
          dist[newX][newY] = min(dist[newX][newY], newW);
          tel[newX][newY] = max(tel[newX][newY], newT);
          pq.push({newX, newY, newW, newT});
        }
      }
    }
    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < m; j++) {
    //     cout << dist[i][j] << " ";
    //   }
    //   cout << "\n";
    // }
    return dist[n - 1][m - 1];
  }
};
