#include <bits/stdc++.h>
using namespace std;
int kol[10], ans = -1, ans0 = 0;
vector<int> a, b;
int main() {
  memset(kol, 0, sizeof(kol));
  char c;
  while (cin >> c) kol[c - '0']++;
  for (int i = 1; i < 10; i++) {
    vector<int> c, d;
    int K1[10], K2[10], res = 0, nul = 0;
    for (int j = 0; j < 10; j++) {
      K1[j] = kol[j];
      K2[j] = kol[j];
    }
    if (K1[i] > 0 && K2[10 - i] > 0) {
      c.push_back(i);
      d.push_back(10 - i);
      K1[i]--;
      K2[10 - i]--;
      res++;
      for (int j = 0; j < 10; j++) {
        while (K1[j] > 0 && K2[9 - j] > 0) {
          K1[j]--;
          K2[9 - j]--;
          c.push_back(j);
          d.push_back(9 - j);
          res++;
        }
      }
    }
    while (K1[0] > 0 && K2[0] > 0) {
      K1[0]--;
      K2[0]--;
      res++;
      nul++;
    }
    for (int j = 0; j < 10; j++) {
      while (K1[j] > 0) {
        K1[j]--;
        c.push_back(j);
      }
      while (K2[j] > 0) {
        K2[j]--;
        d.push_back(j);
      }
    }
    if (res > ans) {
      ans = res;
      ans0 = nul;
      a.swap(c);
      b.swap(d);
    }
  }
  for (int i = a.size() - 1; i >= 0; i--) cout << a[i];
  for (int i = 0; i < ans0; i++) cout << 0;
  cout << endl;
  for (int i = a.size() - 1; i >= 0; i--) cout << b[i];
  for (int i = 0; i < ans0; i++) cout << 0;
}
