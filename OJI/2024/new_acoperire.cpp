
#include <bits/stdc++.h>
using namespace std;

struct Interval {
  double l, r;
};

bool can(double X, int K, vector<Interval> &iv) {
  vector<pair<double, double>> v;

  for (auto &it : iv) {
    double S = it.l, D = it.r;
    double L = D - S;
    if (X < L / 2)
      return false;

    double mid = (S + D) / 2;
    double d = X - L / 2;
    v.push_back({mid - d, mid + d});
  }

  sort(v.begin(), v.end(),
       [](auto &a, auto &b) { return a.second < b.second; });

  int used = 0;
  double last = -1e18;

  for (auto &it : v) {
    if (it.first > last) {
      used++;
      last = it.second;
      if (used > K)
        return false;
    }
  }
  return true;
}

vector<double> build(double X, int K, vector<Interval> &iv) {
  vector<pair<double, double>> v;
  for (auto &it : iv) {
    double L = it.r - it.l;
    double mid = (it.l + it.r) / 2;
    double d = X - L / 2;
    v.push_back({mid - d, mid + d});
  }

  sort(v.begin(), v.end(),
       [](auto &a, auto &b) { return a.second < b.second; });

  vector<double> centers;
  double last = -1e18;

  for (auto &it : v) {
    if (it.first > last) {
      centers.push_back(it.second);
      last = it.second;
    }
  }
  return centers;
}

void print(double x) {
  if (abs(x - round(x)) < 1e-6)
    cout << (long long)round(x);
  else
    cout << fixed << setprecision(1) << x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<Interval> iv(N);

  double low = 0;
  for (int i = 0; i < N; i++) {
    cin >> iv[i].l >> iv[i].r;
    low = max(low, (iv[i].r - iv[i].l) / 2);
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int K;
    cin >> K;

    double l = low, r = 1e8, ans = r;

    for (int it = 0; it < 60; it++) {
      double m = (l + r) / 2;
      if (can(m, K, iv)) {
        ans = m;
        r = m;
      } else {
        l = m;
      }
    }

    auto centers = build(ans, K, iv);

    print(ans);
    cout << "\n";
    cout << centers.size() << "\n";

    for (double c : centers) {
      print(c - ans);
      cout << " ";
      print(c + ans);
      cout << "\n";
    }
  }
}
