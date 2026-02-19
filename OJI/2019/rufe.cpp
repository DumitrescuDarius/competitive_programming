#include <bits/stdc++.h>
#include <fstream>
#define ll long long
using namespace std;

ifstream fin("rufe.in");
ofstream fout("rufe.out");

ll n, m;

ll sum_arithmetic(ll x) {
  if (x <= 0)
    return 0;
  return x * (x + 1) / 2;
}

ll calculateFreeSpace(ll x, ll y, ll r) {
  ll R = r - 1;
  if (R < 0)
    return 0;
  if (R == 0)
    return 1;

  // Total area of the Manhattan diamond: 2*R*(R+1) + 1
  // We use __int128 if n, m are up to 10^9 to prevent overflow during calc
  unsigned __int128 total =
      (unsigned __int128)2 * R * R + (unsigned __int128)2 * R + 1;

  ll d_top = x - 1;
  ll d_bottom = n - x;
  ll d_left = y - 1;
  ll d_right = m - y;

  // Subtract triangles sticking out of the 4 edges
  total -= sum_arithmetic(R - d_top);
  total -= sum_arithmetic(R - d_bottom);
  total -= sum_arithmetic(R - d_left);
  total -= sum_arithmetic(R - d_right);

  // Add back corner overlaps (Inclusion-Exclusion)
  auto get_corner = [&](ll d1, ll d2) {
    ll height = R - d1 - d2 - 1;
    return sum_arithmetic(height);
  };

  total += get_corner(d_top, d_left);
  total += get_corner(d_top, d_right);
  total += get_corner(d_bottom, d_left);
  total += get_corner(d_bottom, d_right);

  return (ll)total;
}

int main() {
  ll a, b, k;
  if (!(fin >> n >> m >> a >> b >> k))
    return 0;

  // If k is 0, the distance is 0
  if (k == 0) {
    fout << 0;
    return 0;
  }

  ll left = 1, right = n + m;
  ll ans = 0;

  while (left <= right) {
    ll mid = left + (right - left) / 2;
    // Check if the number of cells within distance mid-1 is >= k
    if (calculateFreeSpace(a, b, mid) >= k) {
      ans = mid;
      right = mid - 1; // Try to find a smaller distance that still covers k
    } else {
      left = mid + 1;
    }
  }

  fout << ans;
  return 0;
}
