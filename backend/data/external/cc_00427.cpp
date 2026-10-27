#include <bits/stdc++.h>
using namespace std;
int a[100009];
int x[100009];
int y[100009];
int main() {
  int n, m = 0, l = 0, xl = 0, yl = 0, mm, ll = 0;
  scanf("%I32d\n", &n);
  for (int i = 0; i < n; i++) {
    scanf("%I32d", a + i);
    mm += a[i];
  }
  if (mm % n == 0)
    cout << n << endl;
  else
    cout << n - 1 << endl;
  return 0;
}
