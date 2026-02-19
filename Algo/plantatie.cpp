#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("plantatie.in");
ofstream fout("plantatie.out");

vector<vector<int>> tree;
vector<vector<int>> matrix;
const int INF = 1e9;
int N, M;

void buildY(int nodeX, int startX, int endX, int nodeY, int startY, int endY) {
  if (startY == endY) {
    if (startX == endX)
      tree[nodeX][nodeY] = matrix[startX][startY];
    else
      tree[nodeX][nodeY] =
          max(tree[nodeX * 2][nodeY], tree[nodeX * 2 + 1][nodeY]);
  } else {
    int mid = (startY + endY) / 2;
    buildY(nodeX, startX, endX, nodeY * 2, startY, mid);
    buildY(nodeX, startX, endX, nodeY * 2 + 1, mid + 1, endY);

    tree[nodeX][nodeY] =
        max(tree[nodeX][nodeY * 2], tree[nodeX][nodeY * 2 + 1]);
  }
}

void buildX(int nodeX, int startX, int endX) {
  if (startX != endX) {
    int mid = (startX + endX) / 2;
    buildX(nodeX * 2, startX, mid);
    buildX(nodeX * 2 + 1, mid + 1, endX);
  }
  buildY(nodeX, startX, endX, 1, 1, M);
}

int queryY(int nodeX, int nodeY, int startY, int endY, int y1, int y2) {
  if (y1 > endY || y2 < startY)
    return -INF;
  if (y1 <= startY && endY <= y2)
    return tree[nodeX][nodeY];

  int mid = (startY + endY) / 2;
  return max(queryY(nodeX, nodeY * 2, startY, mid, y1, y2),
             queryY(nodeX, nodeY * 2 + 1, mid + 1, endY, y1, y2));
}

int queryX(int nodeX, int startX, int endX, int x1, int x2, int y1, int y2) {
  if (x1 > endX || x2 < startX)
    return -INF;
  if (x1 <= startX && endX <= x2)
    return queryY(nodeX, 1, 1, M, y1, y2);

  int mid = (startX + endX) / 2;
  return max(queryX(nodeX * 2, startX, mid, x1, x2, y1, y2),
             queryX(nodeX * 2 + 1, mid + 1, endX, x1, x2, y1, y2));
}

int main() {
  int q;
  fin >> N >> q;
  M = N;
  tree.assign(N * 4, vector<int>(M * 4, -INF));
  matrix.assign(N + 1, vector<int>(M + 1));
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++)
      fin >> matrix[i][j];
  buildX(1, 1, N);
  for (int i = 0; i < q; i++) {
    int x1, y1, x2, y2, k;
    fin >> x1 >> y1 >> k;
    x2 = x1 + k - 1;
    y2 = y1 + k - 1;
    fout << queryX(1, 1, N, x1, x2, y1, y2) << "\n";
  }
  return 0;
}
