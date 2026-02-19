#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main() {
  int n;
  cin >> n;
  bool active = 0;
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    x ^= active;
    if (x) {
      active ^= 1;
      ans.push_back(i);
    }
  }
  cout << ans.size() << "\n";
  for (auto it : ans)
    cout << it << " ";
  return 0;
}
