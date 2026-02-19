#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// MOVE THESE OUTSIDE MAIN to avoid Stack Overflow
int st[10][501][501];
int lg2[501];

int main() {
  ifstream fin("plantatie.in");
  ofstream fout("plantatie.out");

  int N, Q;
  // Check if file opened successfully
  if (!fin || !(fin >> N >> Q))
    return 0;

  // 1. Precompute logarithms
  for (int i = 2; i <= N; i++) {
    lg2[i] = lg2[i / 2] + 1;
  }

  // 2. Read base matrix
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      fin >> st[0][i][j];
    }
  }

  // 3. Build Sparse Table
  for (int k = 1; k <= lg2[N]; k++) {
    int side = (1 << k);
    int half = (1 << (k - 1));
    for (int i = 1; i + side - 1 <= N; i++) {
      for (int j = 1; j + side - 1 <= N; j++) {
        st[k][i][j] =
            max({st[k - 1][i][j], st[k - 1][i + half][j],
                 st[k - 1][i][j + half], st[k - 1][i + half][j + half]});
      }
    }
  }

  // 4. Answer Queries
  for (int i = 0; i < Q; i++) {
    int x, y, k;
    if (!(fin >> x >> y >> k))
      break;

    int p = lg2[k];
    int diff = k - (1 << p);

    // O(1) query using 4 overlapping squares
    int res = max({st[p][x][y], st[p][x + diff][y], st[p][x][y + diff],
                   st[p][x + diff][y + diff]});

    fout << res << "\n";
  }

  return 0;
}
