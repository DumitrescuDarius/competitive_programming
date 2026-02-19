#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("rmq.in");
ofstream fout("rmq.out");
int main() {
  int n, q;
  fin >> n >> q;
  vector<int> a(n + 1, 0);
  int blockSize = sqrt(n + 1);
  int nrBlocks = (n + blockSize - 1) / blockSize;
  vector<int> b(nrBlocks + 1, INT_MAX);
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    a[i] = x;
    b[i / blockSize] = min(b[i / blockSize], x);
  }
  for (int i = 0; i < q; i++) {
    int left, right, ans = INT_MAX;
    fin >> left >> right;
    while (left <= right && left % blockSize != 0) {
      ans = min(ans, a[left]);
      left++;
    }
    while (left + blockSize - 1 <= right) {
      ans = min(ans, b[left / blockSize]);
      left += blockSize;
    }
    while (left <= right && (right + 1) % blockSize != 0) {
      ans = min(ans, a[right]);
      right--;
    }

    fout << ans << "\n";
  }
  return 0;
}
