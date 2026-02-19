#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("golf.in");
ofstream fout("golf.out");
vector<pair<int, int>> delta{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<vector<int>> filledMap;
vector<int> prefC, sufC, prefL, sufL;
int n, m, cnt, N, W, E, S;

bool inBounds(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < m && filledMap[x][y] == 0)
    return 1;
  return 0;
}

void fill(int x, int y, int color) {
  queue<pair<int, int>> q;
  filledMap[x][y] = color;
  q.push({x, y});
  N = x;
  S = x;
  W = y;
  E = y;
  cnt = 1;
  while (!q.empty()) {
    pair<int, int> pos = q.front();
    q.pop();
    for (auto it : delta) {
      int dx = pos.first + it.first;
      int dy = pos.second + it.second;
      if (inBounds(dx, dy)) {
        N = min(N, dx);
        S = max(S, dx);
        W = min(W, dy);
        E = max(E, dy);
        filledMap[dx][dy] = color;
        cnt++;
        q.push({dx, dy});
      }
    }
  }
}

int main() {
  int cases, cells = 0;
  fin >> cases >> n >> m;
  filledMap.resize(n, vector<int>(m, 0));
  prefC.resize(m, 0);
  sufC.resize(m, 0);
  prefL.resize(n, 0);
  sufL.resize(n, 0);

  for (int i = 0; i < n; i++) {
    string s;
    fin >> s;
    for (int j = 0; j < m; j++) {
      int ch = s[j] - '0';
      if (!ch)
        filledMap[i][j] = -1;
      else
        cells++;
    }
  }
  int k = 0, maxVal = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (filledMap[i][j] == 0) {
        fill(i, j, ++k);
        if (cases == 2) {
          if (cnt > maxVal) {
            maxVal = cnt;
            ans = 1;
          } else if (cnt == maxVal)
            ans++;
        }
        if (cases == 3) {
          prefC[W] += cnt;
          sufC[E] += cnt;
          prefL[N] += cnt;
          sufL[S] += cnt;
        }
      }
    }
  }
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++)
  //     cout << filledMap[i][j] << " ";
  //   cout << "\n";
  // }

  if (cases == 1) {
    fout << cells;
    return 0;
  }
  if (cases == 2) {
    fout << ans;
    return 0;
  }
  if (cases == 3) {
    // coloane
    for (int i = 1; i < m; i++)
      prefC[i] += prefC[i - 1];
    for (int i = m - 2; i >= 0; i--)
      sufC[i] += sufC[i + 1];

    // linii
    for (int i = 1; i < n; i++)
      prefL[i] += prefL[i - 1];
    for (int i = n - 2; i >= 0; i--)
      sufL[i] += sufL[i + 1];
    int q;
    fin >> q;
    while (q--) {
      char type;
      int pos;
      fin >> type >> pos;
      pos--; // trecem pe index 0-based

      if (type == 'C') {
        int res = 0;
        if (pos - 1 >= 0)
          res += prefC[pos - 1];
        if (pos + 1 < m)
          res += sufC[pos + 1];
        fout << res << "\n";
      }

      if (type == 'L') {
        int res = 0;
        if (pos - 1 >= 0)
          res += prefL[pos - 1];
        if (pos + 1 < n)
          res += sufL[pos + 1];
        fout << res << "\n";
      }
    }
  }
  return 0;
}
