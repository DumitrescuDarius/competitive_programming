// This code is shit.
//                     - Dumitrescu Darius
// Candale al nostru care esti in cloud,
// Sfinteasca-se pbinfo-ul tau
// Fie serverele tale, faca site-ul tau
// Precum in pseudocod, asa si-n C++,
// Problemele tale cele de toate zilele
// Da-ne noua astazi
// Si ne repara noua erorile noastre
// Precum si noi reparam pe solinfo
// Si nu ne duce pe noi la Poli
// Si ne izbaveste de Visalon
// Amin
// In numele lui Candale, si al lui Visalon, si al sfantului compilator, Amin
#include <bits/stdc++.h>
#include <vector>
#define int long long
using namespace std;
ifstream fin("experimente.in");
ofstream fout("experimente.out");
const int LOG = 30;
// Freddy Fazbear tree
vector<int> tree;
int n;

// Please mr Fazbear update my tree
void update(int pos, int val) {
  while (pos <= n) {
    tree[pos] += val;
    pos += pos & -pos;
  }
}

int query(int pos) {
  int sum = 0;
  while (pos > 0) {
    sum += tree[pos];
    pos -= pos & -pos;
  }
  return sum;
}

// Thank you mr fazbear for giving me the leftmost K
int find_left(int k) {
  int pos = 0;
  for (int i = LOG; i >= 0; i--) {
    if (pos + (1 << i) <= n && tree[pos + (1 << i)] < k) {
      k -= tree[pos + (1 << i)];
      pos += (1 << i);
    }
  }
  return pos + 1;
}

// Thank you mr fazbear for giving me the leftmost K
int find_right(int k) {
  int pos = 0;
  for (int i = LOG; i >= 0; i--) {
    if (pos + (1 << i) <= n && tree[pos + (1 << i)] <= k) {
      k -= tree[pos + (1 << i)];
      pos += (1 << i);
    }
  }
  return pos;
}

signed main() {
  int m, r = -1, lastX, lastY;
  fin >> n >> m;
  tree.resize(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int x, y, ax, ay;
    fin >> ax >> ay;
    if (r == -1) {
      x = ax;
      y = ay;
    } else {
      x = (r + ax) % n;
      y = (r + ay) % n;
    }
    x++;
    y++;
    if (x <= y) {
      update(x, 1);
      if (y < n)
        update(y + 1, -1);
    }
    if (x > y) {
      update(x, 1);
      update(1, 1);
      update(y + 1, -1);
    }
    int cnt = 0;
    int left = find_left(i + 1);
    int right = find_right(i + 1);
    cnt = right - left + 1;
    fout << cnt << "\n";
    r = cnt;
  }
  return 0;
}
