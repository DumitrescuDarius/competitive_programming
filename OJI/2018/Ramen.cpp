#include <bits/stdc++.h>
#include <fstream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("ramen.in");
ofstream fout("ramen.out");
int main() {
  int n, d;
  fin >> n >> d;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      orders;
  vector<int> ans(n + 1, 0);
  priority_queue<int> customers;
  for (int i = 0; i < n; i++) {
    int t, p;
    fin >> t >> p;
    orders.push({t + d, i});
    customers.push(t + p);
  }
  while (!customers.empty()) {
    ans[orders.top().second] =
        customers.top() + orders.top().first - customers.top();
    customers.pop();
    orders.pop();
  }
  for (int i = 1; i < ans.size(); i++) {
    fout << ans[i] << "\n";
  }
  return 0;
}
