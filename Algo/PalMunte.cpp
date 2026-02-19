#include <bits/stdc++.h>
#include <vector>
using namespace std;
void print(vector<int> &perm) {
  for (auto it : perm)
    cout << it;
  for (int i = perm.size() - 2; i >= 0; i--)
    cout << perm[i];
  cout << "\n";
}
void backTracking(vector<int> &perm) {
  if (perm.size() == 5) {
    print(perm);
  } else {

    int start;
    if (perm.empty())
      start = 1;
    else
      start = perm.back() + 1;
    for (int i = start; i <= 9; i++) {
      perm.push_back(i);
      backTracking(perm);
      perm.pop_back();
    }
  }
}
int main() {
  vector<int> perm;
  backTracking(perm);
  return 0;
}
