#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c, kq = 0, z;
  cin >> a >> b;
  int N[100005], M[100005];
  vector<int> chan;
  vector<int> le;
  for (int i = 0; i < a; i++) {
    cin >> c;
    N[i] = c;
  }
  for (int n = 0; n < b; n++) {
    cin >> c;
    M[n] = c;
  }
  for (int i = 0; i < a; i++) {
    if (N[i] % 2 == 0)
      chan.push_back(N[i]);
    else
      le.push_back(N[i]);
  }
  for (int n = 0; n < b; n++) {
    if (M[n] % 2 == 0) {
      if (le.size() == 0)
        z = -M[n];
      else
        z = le.back();
      if ((z + M[n]) % 2 == 1) {
        kq++;
        le.pop_back();
      }
    } else {
      if (chan.size() == 0)
        z = -M[n];
      else
        z = chan.back();
      if ((z + M[n]) % 2 == 1) {
        kq++;
        chan.pop_back();
      }
    }
  }
  cout << kq << endl;
}
