#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("nunta.in");
ofstream fout("nunta.out");

set<int> ans;
unordered_set<int> hashSums;

uint64_t hashVec(const vector<int> &v) {
  uint64_t h = 1469598103934665603ULL;
  for (int x : v) {
    h ^= (uint64_t)(x + 1000000007);
    h *= 1099511628211ULL;
  }
  return h;
}

void backTracking(vector<int> &v, int n) {
  if (n == 1) {
    ans.insert(v[0]);
    return;
  }

  uint64_t h = hashVec(vector<int>(v.begin(), v.begin() + n));
  if (hashSums.count(h))
    return;
  hashSums.insert(h);

  for (int i = 0; i + 1 < n; i++) {
    int old = v[i];
    v[i] = abs(v[i] - v[i + 1]);

    // Move v[i+1] to end temporarily
    swap(v[i + 1], v[n - 1]);
    backTracking(v, n - 1);
    swap(v[i + 1], v[n - 1]);

    v[i] = old;
  }
}

int main() {
  int n;
  fin >> n;
  vector<int> v(n, 0);
  for (int i = 0; i < n; i++)
    fin >> v[i];

  backTracking(v, n);

  fout << ans.size() << "\n";
  for (auto it : ans)
    fout << it << " ";
  return 0;
}
