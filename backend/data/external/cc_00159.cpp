#include <bits/stdc++.h>
using namespace std;
inline int qpow(int b, int e, int m = 998244353) {
  int a = 1;
  for (; e; e >>= 1, b = (long long)b * b % m)
    if (e & 1) a = (long long)a * b % m;
  return a;
}
int n, k;
int a[300005], b[300005];
void Calc(int lb, int rb, int &x0, int &x1, int &x2, int &x3) {
  if (rb - lb + 1 == 4) {
    int e1 = b[lb] + b[lb + 1];
    int e2 = b[rb] + b[rb - 1];
    if (!e1 && !e2)
      x0 = 0, x1 = x2 = x3 = -0x3f3f3f3f;
    else if (!e1 || !e2) {
      if (e1 + e2 == 1)
        x1 = 2, x2 = 3, x0 = x3 = -0x3f3f3f3f;
      else
        x3 = 4, x1 = 2, x2 = 3, x0 = -0x3f3f3f3f;
    } else
      x1 = 3, x2 = 4, x3 = 5, x0 = -0x3f3f3f3f;
    return;
  }
  int mid = (lb + rb) / 2;
  int lx0, lx1, lx2, lx3, rx0, rx1, rx2, rx3;
  Calc(lb, mid, lx0, lx1, lx2, lx3);
  Calc(mid + 1, rb, rx0, rx1, rx2, rx3);
  x0 = x1 = x2 = x3 = -0x3f3f3f3f;
  x0 = max(x0, lx0 + rx0);
  x1 = max({x1, lx0 + rx1 + 1, lx1 + rx0 + 1, lx1 + rx1 + 1});
  x2 = max({x2, lx0 + rx2 + 2, lx2 + rx0 + 2, lx2 + rx2 + 2});
  x3 = max({x3, lx0 + rx3 + 3, lx3 + rx0 + 3, lx1 + rx2 + 3, lx2 + rx1 + 3,
            lx1 + rx3 + 3, lx3 + rx1 + 3, lx2 + rx3 + 3, lx3 + rx2 + 3,
            lx3 + rx3 + 3});
}
int main() {
  int tests = 1;
  while (tests--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= (k); ++i) scanf("%d", a + i), b[a[i]] = 1;
    int x0, x1, x2, x3;
    Calc(1, 1 << n, x0, x1, x2, x3);
    printf("%d\n", max({x0, x1 + 1, x2 + 1, x3 + 1}));
  }
  return 0;
}
