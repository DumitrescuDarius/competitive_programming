#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
  ll mostBooked(ll n, vector<vector<ll>> &meetings) {
    sort(meetings.begin(), meetings.end());
    for (auto it : meetings) {
      ll dist = it[1] - it[0] + 1;
    }
    return 0;
  }
};
