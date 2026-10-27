#include <bits/stdc++.h>
using namespace std;
int a[10], b[10];
char c[300001], d[300001];
int main() {
  cin >> c;
  int m, n = strlen(c);
  m = n;
  for (int i = 0; i < n; i++) {
    a[c[i] - '0']++;
    b[c[i] - '0']++;
  }
  int q = 1, i, st = -1, mx = 0, mn, col;
  for (int i = 1; i <= 9; i++) {
    if (!a[i]) continue;
    if (!b[10 - i]) continue;
    a[i]--;
    b[10 - i]--;
    col = 1;
    for (int i = 0; i <= 9; i++) col += min(a[i], b[9 - i]);
    if (col > mx) mx = col, st = i;
    a[i]++;
    b[10 - i]++;
  }
  if (st != -1) {
    a[st]--;
    b[10 - st]--;
    n--;
    c[n] = st + '0';
    d[n] = 10 - st + '0';
    for (int i = 0; i <= 9; i++) {
      mn = min(a[i], b[9 - i]);
      for (int j = 0; j < mn; j++) {
        n--;
        c[n] = i + '0';
        d[n] = 9 - i + '0';
        a[i]--;
        b[9 - i]--;
      }
    }
  }
  q = n - 1;
  mn = min(a[0], b[0]);
  for (int i = 0; i < mn; i++) {
    c[m] = d[m] = '0';
    m++;
    a[0]--;
    b[0]--;
  }
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < a[i]; j++) c[q--] = i + '0';
  q = n - 1;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < b[i]; j++) d[q--] = i + '0';
  cout << c + q + 1 << endl << d + q + 1;
  return 0;
}
