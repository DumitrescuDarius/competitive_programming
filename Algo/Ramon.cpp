#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<vector<int>> adj;

void Ramon(int num) {

  cout << "Lista nr " << num << '\n';
  cout << "Te trezesti, te caci, mananci, te ridici din pat \n";
  if (num > 0)
    Ramon(num - 1);
  cout << "Pula \n";
}

int main() {

  int n, m;
  cin >> n;
  Ramon(n);
  // cin >> n >> m;
  // for(int i = 0; i < m; i ++){
  //   int x, y;
  //   cin >> x >> y;
  // }
}
