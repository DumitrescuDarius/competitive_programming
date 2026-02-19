#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("conway.in");
ofstream fout("conway.out");
vector<vector<int>> delta = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                             {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int n;
vector<vector<int>> conway(vector<vector<int>> &matrix) {
  vector<vector<int>> newMatrix(n + 2, vector<int>(n + 2, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int nrNeighbours = 0;
      for (auto it : delta) {
        int px = i + it[0];
        int py = j + it[1];
        nrNeighbours += matrix[px][py];
      }
      if (matrix[i][j] == 1) {
        if (nrNeighbours < 2 || nrNeighbours > 3)
          newMatrix[i][j] = 0;
        else
          newMatrix[i][j] = 1;
      }
      if (nrNeighbours == 3 && matrix[i][j] == 0)
        newMatrix[i][j] = 1;
    }
  }
  return newMatrix;
}

int main() {
  fin >> n;
  vector<vector<int>> matrix(n + 2, vector<int>(n + 2, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      fin >> matrix[i][j];
  // for (int i = 0; i < k; i++)
  //   matrix = conway(matrix);
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++)
  //     fout << matrix[i][j] << " ";
  //   fout << "\n";
  // }
  while (true) {
    matrix = conway(matrix);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cout << (matrix[i][j] ? "██" : "  ");
      }
      cout << "\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "\033[H";
  }
  return 0;
}
