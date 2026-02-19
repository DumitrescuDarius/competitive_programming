#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("summax.in");
ofstream fout("summax.out");

const int INF_CAI = 2000000001;

// Folosim vectori simpli pentru a economisi memorie (2000x2000 int e ~16MB)
int dp[2002][2002];

int main() {
  int v, n, st, dr;
  if (!(fin >> v >> n >> st >> dr))
    return 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      fin >> mat[i][j];
    }
  }

  // Pasul 1: DP de jos in sus pentru a calcula suma maxima posibila din orice
  // punct pana la baza
  for (int j = 1; j <= n; j++) {
    dp[n][j] = mat[n][j];
    cai[n][j] = 1;
  }

  for (int i = n - 1; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      int varianta_stanga = dp[i + 1][j];
      int varianta_dreapta = dp[i + 1][j + 1];

      dp[i][j] = max(varianta_stanga, varianta_dreapta) + mat[i][j];

      // Pasul 2: Numaram cate cai de suma maxima pornesc din (i, j)
      if (varianta_stanga > varianta_dreapta) {
        cai[i][j] = cai[i + 1][j];
      } else if (varianta_dreapta > varianta_stanga) {
        cai[i][j] = cai[i + 1][j + 1];
      } else {
        // Ambele directii sunt optime, adunam numarul de cai
        long long total = (long long)cai[i + 1][j] + cai[i + 1][j + 1];
        if (total > INF_CAI)
          cai[i][j] = INF_CAI;
        else
          cai[i][j] = (int)total;
      }
    }
  }

  if (v == 1) {
    fout << cai[1][1] << "\n";
  } else {
    // Pasul 3: Reconstructia drumurilor de la st la dr
    for (int k = st; k <= dr; k++) {
      int current_k = k;
      int col = 1;
      fout << "1 "; // Prima linie are mereu coloana 1

      for (int i = 1; i < n; i++) {
        int v_st = dp[i + 1][col];
        int v_dr = dp[i + 1][col + 1];

        if (v_st == v_dr) {
          // Avem doua optiuni optime, decidem pe baza lui current_k
          if (current_k <= cai[i + 1][col]) {
            // Ramanem pe aceeasi coloana (stanga in triunghi)
          } else {
            current_k -= cai[i + 1][col];
            col++; // Mergem pe coloana urmatoare (dreapta in triunghi)
          }
        } else if (v_st < v_dr) {
          col++; // Singura varianta optima e la dreapta
        }
        // Daca v_st > v_dr, col ramane la fel (singura varianta optima e la
        // stanga)

        fout << col << (i == n - 1 ? "" : " ");
      }
      fout << "\n";
    }
  }

  return 0;
}
