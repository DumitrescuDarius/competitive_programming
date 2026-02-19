#include <bits/stdc++.h>

using namespace std;

ifstream fin("zboruri.in");
ofstream fout("zboruri.out");

// Folosim long long pentru a evita overflow la 10^14+
#define int long long
const int INF = 1e18;

struct Edge {
  int to, dist, price;
};

struct State {
  int node, d, p;
  // Priority queue-ul din C++ scoate elementul cel mai MARE,
  // deci inversăm comparatorul pentru a scoate MINIMUL.
  bool operator>(const State &other) const {
    if (d != other.d)
      return d > other.d;
    return p > other.p;
  }
};

int32_t main() { // int32_t pentru main din cauza #define int long long
  int T, n, m, S, F;
  if (!(fin >> T >> n >> m >> S >> F))
    return 0;

  vector<vector<Edge>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, d, p;
    fin >> u >> v >> d >> p;
    adj[u].push_back({v, d, p});
  }

  vector<int> minDist(n + 1, INF);
  vector<int> minPrice(n + 1, INF);
  vector<int> parent(n + 1, 0);

  priority_queue<State, vector<State>, greater<State>> pq;

  minDist[S] = 0;
  minPrice[S] = 0;
  pq.push({S, 0, 0});

  while (!pq.empty()) {
    State cur = pq.top();
    pq.pop();

    // Verificăm dacă am găsit deja o variantă mai bună (durată sau preț)
    if (cur.d > minDist[cur.node])
      continue;
    if (cur.d == minDist[cur.node] && cur.p > minPrice[cur.node])
      continue;

    for (auto &edge : adj[cur.node]) {
      int nextD = cur.d + edge.dist;
      int nextP = cur.p + edge.price;

      // Condiția de bază Dijkstra: durată mai mică SAU durată egală dar preț
      // mai mic
      if (nextD < minDist[edge.to] ||
          (nextD == minDist[edge.to] && nextP < minPrice[edge.to])) {
        minDist[edge.to] = nextD;
        minPrice[edge.to] = nextP;
        parent[edge.to] =
            cur.node; // Salvăm tatăl pentru reconstrucția drumului
        pq.push({edge.to, nextD, nextP});
      }
    }
  }

  // Dacă destinația e inaccesibilă
  if (minDist[F] == INF) {
    fout << -1 << endl;
    return 0;
  }

  if (T == 1) {
    // Reconstruim drumul de la F la S folosind vectorul de tați
    vector<int> path;
    for (int v = F; v != 0; v = parent[v]) {
      path.push_back(v);
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
      fout << path[i] << (i == (int)path.size() - 1 ? "" : " ");
    }
  } else {
    // Pentru T=2 afișăm doar prețul minim calculat
    fout << minPrice[F] << endl;
  }

  return 0;
}
