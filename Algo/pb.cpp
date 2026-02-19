#include <bits/stdc++.h>
using namespace std;
int main() {
  int sum = 0;
  for (int i = 1; i <= 2022; i++) {
    if (i % 3 == 1)
      sum += i;
    else
      sum -= i;
  }
  cout << sum;
  return 0;
}
