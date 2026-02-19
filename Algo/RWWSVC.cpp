#include <bits/stdc++.h>
#include <sstream>
using namespace std;
class Solution {
private:
  string vowel = "aeiou";
  pair<string, ll> reverseAndCount(string s) {
    string clone;
    ll cnt = 0;
    for (ll i = s.size() - 1; i >= 0; i--) {
      clone += s[i];
      cnt += (vowel.find(s[i]) != string::npos);
    }
    return {clone, cnt};
  }

public:
  string reverseWords(string s) {
    stringstream ss(s);
    string line, ans;
    ss >> line;
    pair<string, ll> wordData = reverseAndCount(line);
    ll required = wordData.second;
    ans += line + " ";
    while (ss >> line) {
      wordData = reverseAndCount(line);
      if (wordData.second == required)
        ans += wordData.first;
      else
        ans += line;
      ans += " ";
    }
    ans.pop_back();
    return ans;
  }
};
