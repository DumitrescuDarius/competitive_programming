#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <vector>
#define int long long
using namespace std;
ifstream fin("factfact.in");
ofstream fout("factfact.out");
vector<int> fact(14, 0);

void generateFact() {
  int p = 1;
  fact[0] = 1;
  for (int i = 1; i < fact.size(); i++) {
    p *= i;
    fact[i] = p;
  }
}

bool checkFact(int num) {
  int i;
  for (i = 0; i < fact.size() && fact[i] < num; i++)
    ;
  if (fact[i] == num)
    return 1;
  return 0;
}

signed main() {
  generateFact();
  int cases;
  fin >> cases;
  if (cases == 1) {
    int n;
    fin >> n;
    int leftSide, rightSide;
    int ans = 0;
    for (int p = 10; p < n; p *= 10) {
      leftSide = n / p;
      rightSide = n % p;
      if (floor(log10(rightSide) + 1) == floor((log10(p))))
        ans = ans | ((checkFact(leftSide) & checkFact(rightSide)));
    }
    fout << ans;
  }
  if (cases == 2) {
    int nr, ans = 0;
    fin >> nr;
    for (int i = 0; i < nr; i++) {
      int n;
      fin >> n;
      int leftSide, rightSide;
      for (int p = 10; p < n; p *= 10) {
        leftSide = n / p;
        rightSide = n % p;
        if (floor(log10(rightSide) + 1) == floor((log10(p))) &&
            ((checkFact(leftSide) & checkFact(rightSide)) == 1))
          ans = max(ans, n);
      }
    }
    fout << ans;
  }
  if (cases == 3) {
    int nr, maxVal = 0, ans = 0;
    fin >> nr;
    vector<int> nums;
    for (int i = 0; i < nr; i++) {
      int n;
      fin >> n;
      nums.push_back(n);
      int leftSide, rightSide;
      for (int p = 10; p < n; p *= 10) {
        leftSide = n / p;
        rightSide = n % p;
        if (floor(log10(rightSide) + 1) == floor((log10(p))) &&
            ((checkFact(leftSide) & checkFact(rightSide)) == 1))
          maxVal = max(maxVal, n);
      }
    }
    int ct = 0;
    bool check = 0;
    for (auto it : nums) {
      int leftSide, rightSide;
      if (maxVal == it)
        check = 1;
      bool isGood = 0;
      for (int p = 10; p < it; p *= 10) {
        leftSide = it / p;
        rightSide = it % p;
        if (floor(log10(rightSide) + 1) == floor((log10(p))) &&
            ((checkFact(leftSide) & checkFact(rightSide)) == 1))
          isGood = isGood | 1;
      }
      if (isGood) {
        ct++;
        if (check)
          ans = max(ans, ct);
      } else {
        ct = 0;
        check = 0;
      }
    }
    fout << ans;
  }
}
