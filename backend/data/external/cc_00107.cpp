#include <bits/stdc++.h>
using namespace std;
int n;
int a[60];
int ansa[60], ansb[60];
int sum, mi = 0;
struct ele {
  int pos, rest, nowv;
  ele(int pos, int rest, int nowv) : pos(pos), rest(rest), nowv(nowv) {}
  ele() {}
  bool operator<(const ele b) const {
    return (pos == b.pos) ? ((rest == b.rest) ? nowv < b.nowv : rest < b.rest)
                          : pos < b.pos;
  }
};
int aa[60], bb[60];
int ca = 0, cb = 0;
int maxa = 0;
int f[50][25 * 50000];
void DP(int pos, int rest, int nowv) {
  if ((nowv >= (sum - nowv)) && (nowv - (sum - nowv) >= maxa)) return;
  if (ca == (n >> 1) && cb == (n >> 1)) {
    if (max(nowv, sum - nowv) < mi) {
      mi = max(nowv, sum - nowv);
      for (register int i = 1; i <= ca; i++) ansa[i] = aa[i];
      for (register int i = 1; i <= cb; i++) ansb[i] = bb[i];
    }
    return;
  } else if (nowv >= (sum - nowv) && nowv >= mi)
    return;
  else if (f[pos][nowv] & (1 << rest))
    return;
  else {
    f[pos][nowv] |= (1 << rest);
    if (cb < (n >> 1)) bb[++cb] = a[pos], DP(pos + 1, rest, nowv), --cb;
    if (ca < (n >> 1))
      aa[++ca] = a[pos], DP(pos + 1, rest + 1, nowv + a[pos]), --ca;
  }
}
int main() {
  int _n;
  scanf("%d", &n), _n = n;
  for (register int i = 1; i <= n; i++) scanf("%d", a + i);
  for (register int i = 1; i <= n; i++) scanf("%d", a + n + i);
  n <<= 1;
  sort(a + 1, a + 1 + n);
  int ans1 = a[1], ans2 = a[2];
  n -= 2;
  for (register int i = 1; i <= n; i++)
    a[i] = a[i + 2], sum += a[i], maxa = max(maxa, a[i]);
  mi = sum + 1;
  DP(1, 0, 0);
  printf("%d", ans1);
  for (register int i = 1; i <= (n >> 1); i++) printf(" %d", ansa[i]);
  printf("\n");
  for (register int i = (n >> 1); i >= 1; i--) printf("%d ", ansb[i]);
  printf("%d", ans2);
  printf("\n");
  return 0;
}
