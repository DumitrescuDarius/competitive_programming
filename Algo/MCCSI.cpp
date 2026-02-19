#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
private:
  const int inf = 1e9 + 7;

public:
  long long minimumCost(string source, string target, vector<char> &original,
                        vector<char> &changed, vector<int> &cost) {
    int n = 26;
    long long ans = 0;
    vector<vector<long long>> adj(26, vector<long long>(26, inf));
    for (int i = 0; i < 26; i++)
      adj[i][i] = 0;
    for (int i = 0; i < original.size(); i++)
      adj[original[i] - 'a'][changed[i] - 'a'] =
          min(adj[original[i] - 'a'][changed[i] - 'a'], (long long)cost[i]);

    for (int k = 0; k < 26; k++) {
      for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
          if (adj[i][k] == inf || adj[k][j] == inf)
            continue;
          adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        }
      }
    }

    for (int i = 0; i < source.size(); i++) {
      int first = source[i] - 'a';
      int last = target[i] - 'a';
      if (adj[first][last] == inf)
        return -1;
      ans += adj[first][last];
    }
    return ans;
  }
};
