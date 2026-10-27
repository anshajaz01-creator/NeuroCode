#include <bits/stdc++.h>
const long long MOD = 998244353;
int N, C, a[3001];
long long tw[3001][3001], end[3001], O[3001], p2m1[3001], ip2m1[3001], f[3001],
    g[3001];
int count[3001];
long long F[3001][1024];
long long POWER(long long a, long long b) {
  long long r = 1;
  for (; b; b >>= 1) {
    if (b & 1) r = r * a % MOD;
    a = a * a % MOD;
  }
  return r;
}
int main() {
  scanf("%d%d", &N, &C);
  for (int i = 1; i <= N; i++) scanf("%d", a + i);
  if (C > 10) {
    p2m1[0] = 0;
    for (int i = 1; i <= 3000; i++) {
      p2m1[i] = (p2m1[i - 1] * 2 + 1) % MOD;
      ip2m1[i] = POWER(p2m1[i], MOD - 2);
    }
    for (int i = 0; i <= N; i++) {
      for (int j = 1; j <= C; j++) count[j] = 0;
      int zeroes = C;
      long long S = 1;
      for (int j = i + 1; j <= N; j++) {
        if (count[a[j]] == 0) {
          zeroes--;
          count[a[j]]++;
        } else {
          S = S * ip2m1[count[a[j]]] % MOD;
          S = S * p2m1[++count[a[j]]] % MOD;
        }
        if (zeroes == 0)
          tw[i][j] = S * ip2m1[count[a[j]]] % MOD;
        else
          tw[i][j] = 0;
      }
      end[i] = (p2m1[N - i] + 1 - (zeroes ? 0 : S) + MOD) % MOD;
    }
    f[0] = 1;
    for (int i = 0; i <= N / C; i++) {
      for (int j = 0; j <= N; j++) g[j] = 0;
      for (int j = 0; j <= N; j++)
        if (f[j]) {
          for (int k = j + 1; k <= N; k++)
            g[k] = (g[k] + f[j] * tw[j][k]) % MOD;
          O[i] = (O[i] + f[j] * end[j]) % MOD;
        }
      for (int j = 0; j <= N; j++) f[j] = g[j];
    }
    O[0] = (O[0] - 1 + MOD) % MOD;
    for (int i = 0; i <= N; i++) printf("%lld%c", O[i], " \n"[i == N]);
  } else {
    F[0][0] = 1;
    for (int i = 1; i <= N; i++)
      for (int j = N / C; j >= 0; j--)
        for (int k = (1 << C) - 2; k >= 0; k--)
          if (F[j][k]) {
            if ((k | 1 << a[i] - 1) == (1 << C) - 1)
              F[j + 1][0] = (F[j + 1][0] + F[j][k]) % MOD;
            else
              F[j][k | 1 << a[i] - 1] =
                  (F[j][k | 1 << a[i] - 1] + F[j][k]) % MOD;
          }
    for (int i = 0; i <= N; i++) {
      long long O = 0;
      for (int j = 0; j < 1 << C; j++) O = (O + F[i][j]) % MOD;
      if (i == 0) O = (O - 1 + MOD) % MOD;
      printf("%lld%c", O, " \n"[i == N]);
    }
  }
  return 0;
}
