#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
using namespace std;
vector<double> midPos;
ifstream fin("acoperire.in");
ofstream fout("acoperire.out");

void rm(double n) {
  if (n == (int)n)
    fout << (int)n;
  else
    fout << n;
}

bool check(double len, int k) {
  double check = -1e8;
  for (auto it : midPos) {
    if (it > check + len) {
      check = it;
      k--;
    }
    if (k < 0)
      return 0;
  }
  return 1;
}

int cntRemain(double len, int k) {
  double check = -1e8;
  int clone = k;
  for (auto it : midPos) {
    if (it > check + len) {
      check = it;
      k--;
    }
  }
  return clone - k;
}

void prinAns(double len, int k) {
  double check = -1e8;
  double right = -1;
  vector<pair<double, double>> ans;
  for (auto it : midPos) {
    if (it > check + len) {
      if (right != -1) {
        rm(check / 2);
        fout << " ";
        rm(right / 2);
        fout << "\n";
      }
      check = it;
    }
    right = it;
  }
  rm(check / 2);
  fout << " ";
  rm(right / 2);
  fout << "\n";
}

int main() {
  fout << fixed << setprecision(1);
  int n;
  double maxLen = 0;
  fin >> n;
  for (int i = 0; i < n; i++) {
    double x, y;
    fin >> x >> y;
    midPos.push_back(x + y);
    maxLen = max(maxLen, y - x);
  }
  sort(midPos.begin(), midPos.end());
  int q;
  fin >> q;
  for (int i = 0; i < q; i++) {
    int k;
    fin >> k;

    int left = maxLen;
    int right = 1e8;
    int sol = -1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (check(mid, k)) {
        sol = mid;
        right = mid - 1;
      } else
        left = mid + 1;
    }
    double len = (double)sol / 2;
    rm(len);
    fout << "\n" << cntRemain(sol, k) << "\n";
    prinAns(sol, k);
  }
}
