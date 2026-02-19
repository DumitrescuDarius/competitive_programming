#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("gems.in");
ofstream fout("gems.out");

int k;
bool inBouns(int x, int y) {
  if (x >= 0 && x < k && y >= 0 && y < k)
    return 1;
  return 0;
}

vector<pair<int, int>> delta = {{-1, -1}, {-1, 0}, {-1, 1}};

int main() {
  int n;
  fin >> n >> k;
  vector<int> prev(k);

  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    v.push_back(x);
  }

  int ans = 0;
  for (int i = 0; i < k; i++) {
    vector<int> cur(k);
    for (int j = 0; j < k; j++) {
      int idx = (i * k + j) % n;
      cur[j] = v[idx];
      int best = 0;
      if (i > 0) {
        for (auto it : delta) {
          int dx = i + it.first;
          int dy = j + it.second;
          if (inBouns(dx, dy))
            best = max(best, prev[dy]);
        }
      }
      cur[j] += best;
    }
    prev = cur;
  }
  int x;

  while (fin >> x)
    ans = max(ans, prev[x - 1]);
  fout << ans;
  return 0;
}
