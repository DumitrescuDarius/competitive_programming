#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
using namespace std;

char voc[] = "aeiou";

bool isVoc(char ch) { return strchr(voc, ch); }
bool isCons(char ch) { return isalpha(ch) && !isVoc(ch); }

int main() {
  char s[255];
  int ans = 0;
  cin.getline(s, sizeof(s));
  for (int i = 1; i < strlen(s) - 1; i++) {
    if (isCons(s[i - 1]) && isVoc(s[i]) && isCons(s[i + 1])) {
      ans++;
    }
  }
  cout << ans;
  return 0;
}
