#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("untitled.in");
ofstream fout("untitled.out");

int k, p, cnt = 0;

map<int, int> queries;

vector<string> ans;

string voc = "aeiou";

string perm;

bool fr[97];

void backTracking() {
  if (perm.size() == k) {
    cnt++;
    if (queries[cnt])
      ans[queries[cnt]] = perm;

    return;
  }
  if (perm.size() == 0) {
    for (char i = 'a'; i < 'a' + k; i++) {
      perm.push_back(i);
      fr[i] = 1;
      backTracking();
      perm.pop_back();
      fr[i] = 0;
    }
  } else {
    bool isVoc = (voc.find(perm.back()) != string::npos);
    for (char i = perm.back() - p; i <= perm.back() + p; i++) {
      if (i < 'a' || i >= 'a' + k)
        continue;
      bool nextIsVoc = (voc.find(i) != string::npos);
      if ((isVoc && nextIsVoc) || fr[i] == 1)
        continue;
      perm.push_back(i);
      fr[i] = 1;
      backTracking();
      perm.pop_back();
      fr[i] = 0;
    }
  }
}

int main() {
  int C;
  fin >> C >> k >> p;
  if (C == 1) {
    int N = 1 << k;
    vector<vector<long long>> dp(N, vector<long long>(k, 0));

    for (int i = 0; i < k; i++)
      dp[1 << i][i] = 1;

    bool isVoc[32] = {};
    for (int i = 0; i < k; i++) {
      char c = 'a' + i;
      isVoc[i] = (voc.find(c) != string::npos);
    }

    for (int mask = 0; mask < N; mask++) {
      for (int last = 0; last < k; last++) {
        if (!(mask & (1 << last)))
          continue;
        long long ways = dp[mask][last];
        if (ways == 0)
          continue;
        for (int next = 0; next < k; next++) {
          if (mask & (1 << next))
            continue;
          if (abs(next - last) > p)
            continue;
          if (isVoc[last] && isVoc[next])
            continue;
          dp[mask | (1 << next)][next] += ways;
        }
      }
    }

    long long ans = 0;
    for (int last = 0; last < k; last++)
      ans += dp[N - 1][last];
    fout << ans << "\n";
  }
  if (C == 2) {
    int Q;
    fin >> Q;
    ans.resize(Q + 1);
    for (int i = 1; i <= Q; i++) {
      int x;
      fin >> x;
      queries[x] = i;
    }
    backTracking();
    for (int i = 1; i <= Q; i++)
      fout << ans[i] << "\n";
  }
}
