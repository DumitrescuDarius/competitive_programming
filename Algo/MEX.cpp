
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int n, k, ans = 0;
    cin >> n >> k;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      v.push_back(x);
    }
    set<int> missing;
    set<int> exist;
    for (int i = 0; i <= n; i++)
      missing.insert(i);
    vector<int> fr(n + 1, 0);

    for (int i = 0; i < k; i++) {
      int val = v[i];
      if (++fr[val] == 1)
        missing.erase(val);
    }
    ans = max(ans, *missing.begin());
    for (int i = k; i < n; i++) {
      int val = v[i], left = v[i - k];
      if (++fr[val] == 1) {
        missing.erase(val);
        exist.insert(val);
      }
      if (--fr[left] == 0) {
        missing.insert(left);
        exist.erase(left);
      }
      ans = max(ans, *missing.begin());
    }

    cout << ans << '\n';
  }
}
