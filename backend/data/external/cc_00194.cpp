#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, c = 0;
  cin >> n >> m;
  vector<int> key;
  vector<int> chest;
  int keyodd = 0, keyeven = 0, chesteven = 0, chestodd = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    chest.push_back(x);
  }
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    key.push_back(x);
  }
  for (int i = 0; i < n; i++) {
    if (chest[i] % 2 == 1)
      chestodd++;
    else
      chesteven++;
  }
  for (int i = 0; i < m; i++) {
    if (key[i] % 2 == 1)
      keyodd++;
    else
      keyeven++;
  }
  int e, f;
  if (chestodd > keyeven)
    e = keyeven;
  else
    e = chestodd;
  if (chesteven > keyodd)
    f = keyodd;
  else
    f = chesteven;
  cout << e + f << endl;
}
