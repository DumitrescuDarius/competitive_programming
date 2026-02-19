#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int maximalRectangle(vector<vector<char>> &matrix) {
    int N = matrix.size();
    int M = matrix[0].size();

    vector<vector<int>> mat(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        mat[i][j] = matrix[i][j] - '0';

    for (int i = 0; i < N; i++)
      for (int j = 1; j < M; j++)
        if (mat[i][j] == 1)
          mat[i][j] += mat[i][j - 1];

    int ans = 0;
    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++) {
        int width = mat[i][j];
        if (width == 0)
          continue;

        int currWidth = width;
        for (int k = j; k < M && mat[k][j] != 0; k++) {
          currWidth = min(currWidth, mat[k][j]);
          int height = k - i + 1;
          ans = max(ans, height * currWidth);
        }

        /*for (int k = j; k >= 0 && mat[k][j] != 0; k++) {
          currWidth = min(currWidth, mat[k][j]);
          int height = k - i + 1;
          ans = max(ans, height * currWidth);
        }*/
      }
    return ans;
  }
};
