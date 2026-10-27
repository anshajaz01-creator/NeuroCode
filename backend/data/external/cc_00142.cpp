#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:60000000")
using namespace std;
const long double eps = 1e-9;
const int inf = (1 << 30) - 1;
const long long inf64 = ((long long)1 << 62) - 1;
const long double pi = 3.1415926535897932384626433832795;
const string task = "B";
template <class T>
T sqr(T x) {
  return x * x;
}
int n, k;
int a[99][99];
int xc, yc;
inline int f(int x, int y) { return abs(x - xc) + abs(y - yc); }
void check(int D) {
  int bs = inf;
  int bx, byl, byr;
  for (int i = 0; i < (int)(k); i++) {
    int cs = 0;
    int cl = D;
    for (int j = 0; j < k; j++) {
      if (cl == 0) {
        cl++;
        cs -= f(i, j - D);
      }
      if (a[i][j] == 0) {
        cl--;
        cs += f(i, j);
      } else {
        cl = D;
        cs = 0;
      }
      if (cl == 0) {
        if (cs < bs) {
          bs = cs;
          bx = i;
          byr = j;
          byl = byr - D + 1;
        }
      }
    }
  }
  if (bs == inf)
    printf("-1\n");
  else {
    printf("%d %d %d\n", bx + 1, byl + 1, byr + 1);
    for (int i = byl; i <= byr; i++) a[bx][i] = 1;
  }
}
int main() {
  scanf("%d%d", &n, &k);
  memset(a, 0, sizeof(a));
  xc = (k + 1) / 2 - 1;
  yc = (k + 1) / 2 - 1;
  for (int i = 0; i < (int)(n); i++) {
    int x;
    scanf("%d", &x);
    check(x);
  }
  return 0;
}
