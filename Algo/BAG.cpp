#include <bits/stdc++.h>
#include <vector>
#define int long long
using namespace std;
signed main() {
  cin.tie(0);
  int cases;
  cin >> cases;
  while (cases--) {
    int n, cnt = 0;
    cin >> n;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++)
      cin >> v[i];
    if (v[0] || v.back())
      cout << "Alice" << "\n";
    else
      cout << "Bob\n";
  }
  return 0;
}
