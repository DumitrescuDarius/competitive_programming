#include <bits/stdc++.h>
#include <cstring>
using namespace std;
int main() {
  char s[255];
  cin.getline(s, sizeof(s));
  int i = 0, cuts = 0;
  while (i < strlen(s)) {
    int j = i, k;
    while (s[i] == s[j])
      j++;
    for (k = j; k < strlen(s); k++)
      if (s[i] == s[k])
        break;
    if (k < strlen(s)) {
      i = k + 1;
      cuts++;
    } else if (i + 1 != j) {
      i = j;
      cuts++;
    } else {
      cout << s[i];
      i++;
    }
  }
  cout << " " << cuts;
  return 0;
}
