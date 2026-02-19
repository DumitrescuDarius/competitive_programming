#include <bits/stdc++.h>
#include <vector>
using namespace std;

const int inf = 1e9 + 7;

class Solution {
private:
  vector<double> calculateArea(double y, vector<vector<int>> &squares) {
    vector<double> areas(2, 0.0);

    for (auto &it : squares) {
      double y1 = it[1];
      double side = it[2];
      double y2 = y1 + side;

      double height_under = max(0.0, min(y, y2) - y1);
      double area_under = height_under * side;
      double area_total = side * side;

      areas[0] += area_under;
      areas[1] += area_total - area_under;
    }

    return areas;
  }

public:
  double separateSquares(vector<vector<int>> &squares) {
    double target = 0;
    double minVal = inf, maxVal = 0;

    for (int i = 0; i < squares.size(); i++) {
      int y1 = squares[i][1];
      int len = squares[i][2];
      int y2 = y1 + len;
      target += (double)len * len;
      minVal = min(minVal, (double)y1);
      maxVal = max(maxVal, (double)y2);
    }

    target /= 2;
    double left = minVal;
    double right = maxVal;
    double diff = 0.00001;

    while (right - left >= diff) {
      double mid = left + right / 2;

      vector<double> areas = calculateArea(mid, squares);

      if (areas[0] <= areas[1])
        left = mid + diff;
      if (areas[0] > areas[1])
        right = mid - diff;
    }
    return left;
  }
};
