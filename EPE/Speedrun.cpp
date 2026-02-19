#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("speedrun.in");
ofstream fout("speedrun.out");
const int inf = 1e9 + 7;

struct Cell {
  int x, y, dist;
  bool hasKey;
};

int N, M;

vector<vector<int>> delta = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

bool inBounds(int x, int y) {
  if (x >= 1 && x <= N && y >= 1 && y <= M)
    return 1;
  return 0;
}

int main() {
  int T, P;
  int L1, C1, L2, C2;

  fin >> T >> N >> M >> P;
  fin >> L1 >> C1 >> L2 >> C2;

  vector<vector<int>> mat(N + 1, vector<int>(M + 1, 0));

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++)
      fin >> mat[i][j];

  queue<Cell> q;

  if (T == 1) {
    vector<vector<int>> dist(N + 1, vector<int>(M + 1, 0));
    dist[L1][C1] = 1;
    q.push({L1, C1});

    while (!q.empty()) {
      Cell cur = q.front();
      q.pop();
      for (auto it : delta) {
        int dx = it[0] + cur.x;
        int dy = it[1] + cur.y;
        if (inBounds(dx, dy) && dist[dx][dy] == 0 && !mat[dx][dy]) {
          dist[dx][dy] = dist[cur.x][cur.y] + 1;
          q.push({dx, dy});
        }
      }
    }

    fout << dist[L2][C2] - 1;
  }
  if (T == 2) {
    vector<vector<pair<int, bool>>> dist(
        N + 1, vector<pair<int, bool>>(M + 1, {inf, 0}));

    set<pair<int, int>> st;

    for (int i = 0; i < P; i++) {
      int x, y;
      fin >> x >> y;
      st.insert({x, y});
    }

    bool isGood = 0;
    if (st.count({L1, C1}))
      isGood = 1;

    q.push({L1, C1, 1, isGood});
    dist[L1][C1] = {1, isGood};

    while (!q.empty()) {
      Cell cur = q.front();
      int X = cur.x;
      int Y = cur.y;
      int D = cur.dist;
      bool K = cur.hasKey;
      q.pop();
      if (dist[X][Y].first <= D && dist[X][Y].second > K)
        continue;
      for (auto it : delta) {
        int dx = X + it[0];
        int dy = Y + it[1];
        int newDist = cur.dist + 1;
        if (inBounds(dx, dy) && mat[dx][dy] == 0) {
          if (newDist < dist[dx][dy].first &&
              cur.hasKey == dist[dx][dy].second) {
            dist[dx][dy].first = newDist;
            K = K | st.count({dx, dy});
            dist[dx][dy].first = K;
            q.push({dx, dy, newDist, K});
          } else if (K == 1 && dist[dx][dy].second == 0) {
            dist[dx][dy].first = newDist;
            dist[dx][dy].second = 1;
            q.push({dx, dy, newDist, K});
          }
        }
      }
    }

    fout << dist[L2][C2].first - 1;
  }
}
