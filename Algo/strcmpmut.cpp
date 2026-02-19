#include <bits/stdc++.h>
#include <tuple>
#include <vector>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;
const int BASE = 1e4 + 7;

struct Node {
  int lazy;
  int len;
  ll hash;
};
// Node structure

vector<Node> tree;
vector<ll> sumBase;
string s;

void preCompute(int len) {
  sumBase.push_back(1);
  for (int i = 1; i <= len; i++) {
    ll add = (sumBase[i - 1] * BASE + 1) % MOD;
    sumBase.push_back(add);
  }
}

ll calcHash(int ch, int len) { return ch * sumBase[len - 1] % MOD; }

void comp(int node, int ch) {
  tree[node].lazy = ch;
  tree[node].hash = calcHash(ch, tree[node].len);
}

void build(int node, int left, int right) {
  tree[node].lazy = -1;
  tree[node].len = right - left + 1;
  if (left == right)
    tree[node].len = 1;
  else {
    int mid = (left + right) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
  }
}

// Build the segment tree with lazy

void push(int node) {
  if (tree[node].lazy != -1) {
    int x = tree[node].lazy;
    tree[node * 2].lazy = tree[node * 2 + 1].lazy = x;
    tree[node].lazy = -1;
  }
}

// Propagation

void update(int node, int left, int right, int uleft, int uright, int ch) {
  if (uright < left || right < uleft)
    return;
  if (uleft <= left && right <= uright) {
    comp(node, ch);
    return;
  }
  push(node);
  int mid = (left + right) / 2;
  update(node * 2, left, mid, uleft, uright, ch);
  update(node * 2, mid + 1, right, uleft, uright, ch);
  tree[node] = merge();
}

// Update intervals

/*
pair<int, int> query(int node, int left, int right, int qleft, int qright) {
  if (qright < left && right < qleft)
    return {INT_MIN, INT_MAX};
  if (qleft <= left && right <= qright)
    return {tree[node].mn, tree[node].mx};

  int mid = (left + right) / 2;
  auto leftTree = query(node * 2, left, mid, qleft, qright);
  auto rightTree = query(node * 2 + 1, mid + 1, right, qleft, qright);
  return {min(leftTree.first, rightTree.first),
          min(leftTree.second, rightTree.second)};
}
*/

// Check the queries

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  tree.resize(s.size() * 4);
  cin >> s;
  preCompute(s.size());
  s.insert(s.begin(), 0);
  build(1, 1, s.size() - 1);
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int type,
  }
}
