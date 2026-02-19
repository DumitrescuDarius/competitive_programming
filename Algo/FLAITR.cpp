#include <bits/stdc++.h>
#include <csignal>
#include <vector>
using namespace std;
class Solution {
public:
  long long largestSquareArea(vector<vector<int>> &bl,
                              vector<vector<int>> &tr) {

    int area = 0;
    for (int i = 0; i < bl.size(); i++) {

      for (int j = i + 1; j < tr.size(); j++) {
        int leftx = max(bl[i][0], bl[j][0]);
        int lefty = max(bl[i][1], bl[j][1]);
        int rightx = min(tr[i][0], tr[j][0]);
        int righty = min(tr[i][1], tr[j][1]);

        if (leftx >= rightx || lefty >= righty)
          continue;
        int len = rightx - leftx;
        len = min(len, righty - lefty);
        area = max(area, len * len);
      }
    }
    return area;
  }
};
