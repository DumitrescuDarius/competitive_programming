#include <bits/stdc++.h>
using namespace std;
int main() {
  int arr[10][10] = {};
  int k, n;
  cin >> k >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      arr[i][j] = k * i - i + j;
}
