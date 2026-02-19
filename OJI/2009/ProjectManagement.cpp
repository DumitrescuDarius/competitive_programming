#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("pm.in");
ofstream fout("pm.out");
const int inf = 1e9 + 7;
int main() {
  int n, ans = 0;
  fin >> n;
  vector<int> v(n + 1, 0);
  vector<int> weight(n + 1, 0);
  vector<int> revWeight(n + 1, inf);
  vector<vector<int>> adj(n + 1);
  vector<vector<int>> revAdj(n + 1);
  vector<int> inDegree(n + 1, 0);
  vector<int> revInDegree(n + 1, 0);
  queue<int> q, revQ;
  for (int i = 1; i <= n; i++)
    fin >> v[i];
  for (int i = 1; i <= n; i++) {
    int k;
    fin >> k;
    inDegree[i] = k;
    if (k == 0) {
      q.push(i);
      weight[i] = v[i];
    }
    for (int j = 0; j < k; j++) {
      int x;
      fin >> x;
      adj[x].push_back(i);
      revAdj[i].push_back(x);
      revInDegree[x]++;
    }
  }

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    ans = max(ans, weight[cur]);
    for (auto it : adj[cur]) {
      if (!--inDegree[it])
        q.push(it);
      weight[it] = max(weight[it], weight[cur] + v[it]);
    }
  }
  fout << ans << "\n";
  for (int i = 1; i <= n; i++)
    if (revInDegree[i] == 0) {
      revQ.push(i);
      revWeight[i] = ans - v[i];
    }
  while (!revQ.empty()) {
    int cur = revQ.front();
    revQ.pop();
    for (auto it : revAdj[cur]) {
      if (!--revInDegree[it])
        revQ.push(it);
      revWeight[it] = min(revWeight[it], revWeight[cur] - v[it]);
    }
  }
  for (int i = 1; i <= n; i++) {
    fout << weight[i] - v[i] << " " << revWeight[i] << "\n";
  }
  return 0;
}
