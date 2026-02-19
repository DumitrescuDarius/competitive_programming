#include <bits/stdc++.h>
#include <vector>
using namespace std;
struct money {
  int value;
  int cnt;
};
vector<money> v;
vector<int> sub;
int n, target;

void print() {
  for (auto it : sub)
    cout << it << " ";
  exit(0);
}

void backTracking(int sum) {
  int pos = sub.size();
  if (pos == n && sum == target)
    print();
  else if (pos < n && sum < target) {
    int add = 0;
    for (int i = 1; i <= v[pos].cnt; i++) {
      add += v[pos].value;
      sub.push_back(i);
      if (sum + add <= target)
        backTracking(sum + add);
      sub.pop_back();
    }
  }
}

int main() {
  cin >> n >> target;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].value;
  for (int i = 0; i < n; i++)
    cin >> v[i].cnt;
  backTracking(0);
  return 0;
}
