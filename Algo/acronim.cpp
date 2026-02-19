#include <bits/stdc++.h>
#include <cstring>
using namespace std;
int main() {
  char s[100];
  cin.getline(s, sizeof(s));
  int pos = 0;
  char *p = strtok(s, " ");
  char ans[100];
  while (p) {
    if (p[0] >= 'A' && p[0] <= 'Z')
      ans[pos++] = p[0];
    p = strtok(NULL, " ");
  }
  ans[pos] = '\0';
  cout << ans;
  return 0;
}
