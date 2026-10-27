#include <bits/stdc++.h>
using namespace std;
const int MAXN = (int)1e6 + 10086;
const int P = 1000000007;
int n, m;
char a[MAXN];
int lb(int x) { return x & -x; }
long long R[MAXN], RR[MAXN];
long long L[MAXN], ll[MAXN];
int Wsum[MAXN], Bsum[MAXN];
int f1[MAXN];
void ins(int f[], int pos, int val) {
  ++pos;
  for (; pos <= n + 1; pos += lb(pos)) f[pos] = (f[pos] + val) % P;
}
int sum(int f[], int pos) {
  ++pos;
  int r = 0;
  for (; pos > 0; pos -= lb(pos)) r = (r + f[pos]) % P;
  return r;
}
long long MOD(long long x) {
  x %= P;
  return x < 0 ? x + P : x;
}
long long lsum(int f[], int l, int r) { return MOD(sum(f, r) - sum(f, l - 1)); }
void dp(char tar, long long RR[], long long R[], int Bsum[]) {
  memset(f1, 0, sizeof f1);
  for (int i = 1; i <= n; ++i)
    Bsum[i] = Bsum[i - 1] + (a[i] != tar && a[i] != 'X');
  RR[0] = 1;
  long long pre = 1;
  for (int i = 1; i <= n; ++i)
    if (a[i] != tar && a[i] != 'X') {
      RR[i] = pre;
    } else {
      ins(f1, i - 1, 1);
      int j;
      long long las = 1;
      for (j = i; j <= n; ++j)
        if (a[j] != tar && a[j] != 'X')
          break;
        else {
          long long fsame = lsum(f1, max(j - m + 1, i - 1), j);
          long long fdiff = lsum(f1, max(j - m, i - 1), j - 1);
          if (a[j] == tar)
            las = fsame;
          else
            las = (fsame + fdiff) % P, ins(f1, j, fdiff);
          RR[j] = pre * las % P;
        }
      pre = pre * las % P;
      i = j - 1;
    }
  for (int i = 0; i < m; ++i) R[i] = 0;
  R[m] = (Bsum[m] == 0);
  for (int i = m + 1; i <= n; ++i) {
    R[i] = RR[i - m - 1] * (a[i - m] != tar) * (Bsum[i] - Bsum[i - m] == 0);
  }
}
int main() {
  while (cin >> n >> m) {
    scanf("%s", a + 1);
    reverse(a + 1, a + 1 + n);
    dp('W', RR, R, Bsum);
    reverse(a + 1, a + 1 + n);
    dp('B', ll, L, Wsum);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
      R[i] = (R[i] + R[i - 1] * (a[n + 1 - i] == 'X' ? 2 : 1)) % P;
    for (int i = 1; i < n; ++i) ans = (ans + L[i] * R[n - i]) % P;
    cout << ans << endl;
  }
  return 0;
}
