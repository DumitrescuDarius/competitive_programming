#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("summax.in");
ofstream fout("summax.out");
vector<vector<pair<int, int>>> dp;
const long long bound = 2e9 + 1;
int n, L, R;
int main() {
  int T;
  fin >> T;
  fin >> n >> L >> R;
  dp.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    dp[i].assign(i + 2, {0, 0});
    for (int j = 1; j <= i; j++) {
      fin >> dp[i][j].first;
      if (i == n)
        dp[i][j].second = 1;
    }
  }
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      if (dp[i + 1][j].first == dp[i + 1][j + 1].first) {
        dp[i][j].first += dp[i + 1][j].first;
        long long sum =
            min(1LL * dp[i + 1][j].second + dp[i + 1][j + 1].second, bound);
        dp[i][j].second = min(sum, bound);
      }
      if (dp[i + 1][j].first > dp[i + 1][j + 1].first) {
        dp[i][j].first += dp[i + 1][j].first;
        dp[i][j].second += dp[i + 1][j].second;
      }
      if (dp[i + 1][j].first < dp[i + 1][j + 1].first) {
        dp[i][j].first += dp[i + 1][j + 1].first;
        dp[i][j].second += dp[i + 1][j + 1].second;
      }
    }
  }
  if (T == 1)
    fout << dp[1][1].second;
  else {
    for (int i = L; i <= R; i++) {
      int cur = i;
      int y = 1;
      fout << y << " ";
      for (int x = 1; x < n; x++) {
        int goLeft = dp[x + 1][y].first, goRight = dp[x + 1][y + 1].first;
        // ignoram cazul goLeft > goRight pt ca nu trb sa schimbam coloana si nu
        // influenteaza parcurgerea
        if (goLeft < goRight)
          y++;
        // ne mutam in dreapta jos
        else if (goLeft == goRight) {
          // daca cur <= dp[x + 1][y].second nu influenteaza codul
          if (cur > dp[x + 1][y].second) {
            cur -= dp[x + 1][y].second;
            y++;
          }
        }
        fout << y << " ";
      }
      fout << "\n";
    }
  }
  return 0;
}
