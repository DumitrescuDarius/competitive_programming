#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("cartele.in");
ofstream fout("cartele.out");
int main() {
  int T, n;
  fin >> T >> n;
  if (T == 1) {
    int Boys = 0, Girls = 0;
    for (int i = 0; i < n; i++) {
      char gen, state;
      int H, M, S;
      fin >> gen >> state >> H >> M >> S;
      if (gen == 'b')
        Boys += (state == 'i') - (state == 'e');
      if (gen == 'f')
        Girls += (state == 'i') - (state == 'e');
    }
    fout << Boys << " " << Girls;
  }
  if (T == 2) {
    vector<int> Boys(1e5, 0), Girls(1e5, 0);
    int F = 0;
    for (int i = 0; i < n; i++) {
      char gen, state;
      int H, M, S;
      fin >> gen >> state >> H >> M >> S;
      int time = H * 3600 + M * 60 + S;
      if (gen == 'b')
        Boys[time] += (state == 'i') - (state == 'e');
      if (gen == 'f')
        Girls[time] += (state == 'i') - (state == 'e');
      F = max(F, time);
    }
    int ans = 0;
    for (int i = 0; i < F; i++) {
      if (i > 0) {
        Boys[i] += Boys[i - 1];
        Girls[i] += Girls[i - 1];
      }
      ans += (Boys[i] == Girls[i]) * (Boys[i] != 0);
    }
    fout << ans;
  }
  if (T == 3) {
    vector<int> Boys(1e5, 0), Girls(1e5, 0);
    int F = 0;
    for (int i = 0; i < n; i++) {
      char gen, state;
      int H, M, S;
      fin >> gen >> state >> H >> M >> S;
      int time = H * 3600 + M * 60 + S;
      if (gen == 'b')
        Boys[time] += (state == 'i') - (state == 'e');
      if (gen == 'f')
        Girls[time] += (state == 'i') - (state == 'e');
      F = max(F, time);
    }
    int ans = 0, cnt = 0;
    cnt = (Boys[0] == Girls[0]) * (Boys[0] != 0);
    for (int i = 1; i <= F; i++) {
      Boys[i] += Boys[i - 1];
      Girls[i] += Girls[i - 1];
      if (Boys[i] % 2 == 0)
        cnt = 0;
      else
        cnt++;
      ans = max(ans, cnt);
    }
    fout << ans;
  }
  return 0;
}
