#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma G++ optimize("O3")
using namespace std;
const double PI = acos(-1.0);
const int MAXN = 5e5 + 55;
const int INF = 0x3f3f3f3f;
const int NINF = 0x80808080;
const long long NLINF = 0x8080808080808080;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-6;
int n;
int a[MAXN];
int lowbit(int x) { return x & -x; }
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  int ans = 0;
  for (int i = 1; i <= n - 1; i++) {
    ans += a[i];
    printf("%d\n", ans);
    int ff = n - i;
    int pre = 1;
    while (ff) {
      pre = ff;
      ff = ff - lowbit(ff);
    }
    a[i + pre] += a[i];
  }
}
