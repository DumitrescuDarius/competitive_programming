#include <bits/stdc++.h>
#include <climits>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("aesm.in");
ofstream fout("aesm.out");

struct Node {
  int mn;
  int cnt;
};
void build(int node, int left, int right, int pos, int val,
           vector<Node> &tree) {
  if (left == right) {
    tree[node].mn = val;
    tree[node].cnt = 1;
  } else {
    int mid = (left + right) / 2;
    if (pos <= mid)
      build(node * 2, left, mid, pos, val, tree);
    else
      build(node * 2 + 1, mid + 1, right, pos, val, tree);
    tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
    tree[node].cnt = tree[node * 2].cnt + tree[node * 2 + 1].cnt;
  }
}
void eraseK(int node, int left, int right, int pos, vector<Node> &tree) {
  if (left == right) {
    tree[node].mn = INT_MAX;
    tree[node].cnt = 0;
  } else {
    int mid = (left + right) / 2;
    if (pos <= tree[node * 2].cnt)
      eraseK(node * 2, left, mid, pos, tree);
    else
      eraseK(node * 2 + 1, mid + 1, right, pos - tree[node * 2].cnt, tree);
    tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
    tree[node].cnt = tree[node * 2].cnt + tree[node * 2 + 1].cnt;
  }
}

void update(int node, int left, int right, int pos, int val,
            vector<Node> &tree) {
  if (left == right) {
    tree[node].mn = val;
    tree[node].cnt = 1;
  } else {
    int mid = (left + right) / 2;
    if (pos <= tree[node * 2].cnt)
      update(node * 2, left, mid, pos, val, tree);
    else
      update(node * 2 + 1, mid + 1, right, pos - tree[node * 2].cnt, val, tree);
    tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
    tree[node].cnt = tree[node * 2].cnt + tree[node * 2 + 1].cnt;
  }
}

int findMinimum(int node, int left, int right, vector<Node> &tree) {
  if (left == right)
    return 1;
  int mid = (left + right) / 2;
  if (tree[node * 2].mn == tree[node].mn)
    return findMinimum(node * 2, left, mid, tree);
  return tree[node * 2].cnt + findMinimum(node * 2 + 1, mid + 1, right, tree);
}

int main() {
  int n;
  fin >> n;
  vector<Node> tree(n * 4, {INT_MAX, 0});
  for (int i = 1; i <= n; i++) {
    int x;
    fin >> x;
    build(1, 1, n, i, x, tree);
  }
  int q;
  fin >> q;
  for (int i = 0; i < q; i++) {
    int type;
    fin >> type;
    if (type == 1) {
      fout << tree[1].mn << "\n";
      int pos = findMinimum(1, 1, n, tree);
      eraseK(1, 1, n, pos, tree);
    } else {
      int pos, x;
      fin >> pos >> x;
      update(1, 1, n, pos, x, tree);
    }
  }
  return 0;
}
