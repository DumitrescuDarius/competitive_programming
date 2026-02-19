#include <bits/stdc++.h>
#include <fstream>
using namespace std;
ifstream fin("galeti.in");
ofstream fout("galeti.out");
int main() {
  int len, target;
  fin >> len >> target;
  printMoves(1, len, target);

  return 0;
}

1(0)1

    1 2

    (1)2(0)1

    1 2 3(2)5(1)4(0)3

    (2)(1)13(0)12
