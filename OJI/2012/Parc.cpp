#include <bits/stdc++.h>
#include <fstream>
#include <utility>
using namespace std;
ifstream fin("parc.in");
ofstream fout("parc.out");

double calcDist(double a, double b) { return sqrt(a * a + b * b); }

int main() {
  int n, m, xG, yG, xpr, ypr;
  fin >> n >> m;
  fin >> xG >> yG >> xpr >> ypr;

  int cols, rows;
  fin >> cols;

  double bikeX = 0;
  for (int i = 0; i < cols; i++) {
    int x, y;
    fin >> x >> y;
    if (x > y)
      swap(x, y);

    int L = max(x, min(xG, xpr));
    int R = min(y, max(xG, xpr));
    if (L < R)
      bikeX += (R - L);
  }

  fin >> rows;

  double bikeY = 0;
  for (int i = 0; i < rows; i++) {
    int x, y;
    fin >> x >> y;
    if (x > y)
      swap(x, y);

    int L = max(x, min(yG, ypr));
    int R = min(y, max(yG, ypr));
    if (L < R)
      bikeY += (R - L);
  }

  if (xpr < xG) {
    swap(xpr, xG);
  }
  if (ypr < yG) {
    swap(ypr, yG);
  }

  double dx = abs(xpr - xG) - bikeX;
  double dy = abs(ypr - yG) - bikeY;

  double dist = calcDist(dx, dy) + bikeX + bikeY;
  fout << dist << "\n";
  fout << 1;
  return 0;
}
