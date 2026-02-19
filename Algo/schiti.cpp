#include <bits/stdc++.h>
#include <cstring>
using namespace std;
int main() {
  char s[101] = {}, c[21] = {}, ans[101] = {};
  bool found = 0;
  cin.getline(s, sizeof(s));
  cin.getline(c, sizeof(c));
  int fr[256] = {};
  for (int i = 0; i < strlen(c); i++)
    fr[c[i]]++;

  char *p = strtok(s, " ");
  while (p) {
    int frWord[256] = {};
    for (int i = 0; i < strlen(p); i++)
      frWord[p[i]]++;
    bool isGood = 1;
    for (int i = 0; i < 256; i++)
      if (frWord[i] != fr[i])
        isGood &= 0;
    if (!isGood) {
      strcat(ans, p);
      strcat(ans, " ");
    }
    p = strtok(NULL, " ");
    found = found | isGood;
  }
  if (found)
    for (int i = 0; i < strlen(ans); i++)
      cout << ans[i];
  else
    cout << "nu exista";
  return 0;
}
