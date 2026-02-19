

#include <bits/stdc++.h>
using namespace std;

ifstream fin("treebits.in");
ofstream fout("treebits.out");

const int MAXN = 200005;

int T, N, Q;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN];
int forced[MAXN][31]; // forced[node][bit] = 1 dacă trebuie 1

void dfs(int u, int par) {
  parent[u] = par;
  for (int v : adj[u]) {
    if (v != par) {
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  }
}

// marcheaza drumul 1 -> K pentru bitul 1
void markPath(int K, int bit) {
  int u = K;
  while (u != 0) {
    forced[u][bit] = 1;
    u = parent[u];
  }
}

bool checkZeroConstraint(int K, int bit) {
  // verificam daca exista cel putin un nod cu forced[node][bit] = 0 pe drumul
  // 1->K
  int u = K;
  while (u != 0) {
    if (forced[u][bit] == 0)
      return true; // nod disponibil cu 0
    u = parent[u];
  }
  return false; // toate sunt 1 -> imposibil
}

void solve() {
  fin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    adj[i].clear();
    for (int b = 0; b <= 30; b++)
      forced[i][b] = 0;
  }

  for (int i = 1; i < N; i++) {
    int a, b;
    fin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<pair<int, int>> queries(Q);
  for (int i = 0; i < Q; i++)
    fin >> queries[i].first >> queries[i].second;

  depth[1] = 0;
  dfs(1, 0);

  bool possible = true;

  for (int bit = 0; bit <= 30; bit++) {
    // mai intai setam nodurile cu bit = 1
    for (auto &q : queries) {
      int K = q.first;
      int V = q.second;
      if ((V >> bit) & 1)
        markPath(K, bit);
    }
    // acum verificam bit = 0
    for (auto &q : queries) {
      int K = q.first;
      int V = q.second;
      if (((V >> bit) & 1) == 0) {
        if (!checkZeroConstraint(K, bit)) {
          possible = false;
          break;
        }
      }
    }
    if (!possible)
      break;
  }

  fout << (possible ? "DA" : "NU");
}

int main() {
  fin >> T;
  for (int t = 0; t < T; t++) {
    solve();
    fout << "\n";
  }
  return 0;
}
