#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
private:
  vector<int> cover;
  vector<int> cnt;
  vector<int> tree;

  void update(int node, int left, int right, int qleft, int qright) {
    if (tree[right] < qleft || tree[left] >= right)
      return;
    if (qleft <= tree[left] && tree[right] < right)
      cnt[node]++;
    else {
      int mid = (left + right) / 2;
      update(node * 2, left, mid, qleft, qright);
      update(node * 2 + 1, mid + 1, right, qleft, qright);
    }
    if (cnt[node] > 0)
      cover[node] = tree[right + 1] - tree[left];
    else if (left == right)
      cover[node] = 0;
    else
      cover[node] = cover[node * 2 + 1] + cover[node * 2 + 2];
  }

public:
  double separateSquares(vector<vector<int>> &squares) {}
};
