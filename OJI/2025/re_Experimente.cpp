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
#include <algorithm>
#include <bits/stdc++.h>
#define int long long
using namespace std;
ifstream fin("experimente.in");
ofstream fout("experimente.out");

signed main() {
  int n, m, tLeft0, tRight0, tLeft1, tRight1;
  bool leftRight = 0;
  fin >> n >> m;
  int left, right;
  fin >> left >> right;
  if (left <= right) {
    tLeft0 = left;
    tRight0 = right;
  } else {
    leftRight = 1;
    tLeft0 = 0;
    tRight0 = left;
    tLeft1 = right;
    tRight1 = n - 1;
  }

  for (int i = 0; i < m; i++) {
    fin >> left >> right;
    if (left <= right && !leftRight) {
      tLeft0 = max(tLeft0, left);
      tRight0 = min(tRight0, right);
    } else if (left <= right && leftRight) {
      tLeft0 = max(tLeft0, left);
      tRight0 = min(tRight0, right);
      tLeft1 = max(tLeft1, left);
      tRight1 = min(tRight1, right);
    } else if (left > right && !leftRight) {
      leftRight = 1;
      tLeft0 = max(tLeft0, 1);
      tRight0 = min(tRight0, left);
    } else if (left > right && leftRight) {
      tLeft0 = max(tLeft0, left);
      tRight0 = min(tRight0, right);
      tLeft1 = max(tLeft1, left);
      tRight1 = min(tRight1, right);
    }
  }
}
