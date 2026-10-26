#include <bits/stdc++.h>
using namespace std;
const int Size = 5007;
const long long Mod = 1e9 + 7;
long long F[55][55][55];
void modify_0(int rt) {
  for (int j = 0; j < rt; ++j) {
    long long k = F[0][j][rt - 1];
    if (k == 0) continue;
    F[0][j + 1][rt] += k * ((1LL << (rt - 1)) % Mod) % Mod;
    F[0][j + 1][rt] %= Mod;
  }
  for (int i = 1; i < rt; ++i)
    for (int j = 0; j + i < rt; ++j) {
      long long k = F[i][j][rt - 1];
      if (k == 0) continue;
      F[i][j + 1][rt] += k * ((1LL << (rt - 2)) % Mod) % Mod;
      F[i][j][rt] += k * ((1LL << (rt - 2)) % Mod) % Mod;
      F[i][j + 1][rt] %= Mod;
      F[i][j][rt] %= Mod;
    }
}
void modify_1(int rt) {
  for (int i = 0; i < rt; ++i) {
    long long k = F[i][0][rt - 1];
    if (k == 0) continue;
    F[i + 1][0][rt] += k * ((1LL << (rt - 1)) % Mod) % Mod;
    F[i + 1][0][rt] %= Mod;
  }
  for (int i = 0; i < rt; ++i)
    for (int j = 1; j + i < rt; ++j) {
      long long k = F[i][j][rt - 1];
      if (k == 0) continue;
      F[i + 1][j][rt] += k * ((1LL << (rt - 2)) % Mod) % Mod;
      F[i][j][rt] += k * ((1LL << (rt - 2)) % Mod) % Mod;
      F[i + 1][j][rt] %= Mod;
      F[i][j][rt] %= Mod;
    }
}
int a[100];
int main() {
  int n, p;
  scanf("%d%d", &n, &p);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  if (a[1] == 0 || a[1] == -1) F[0][1][1] = 1;
  if (a[1] == 1 || a[1] == -1) F[1][0][1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i] == 0)
      modify_0(i);
    else if (a[i] == 1)
      modify_1(i);
    else {
      modify_0(i);
      modify_1(i);
    }
  }
  long long ans = 0;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j + i <= n; ++j) {
      if ((i + j) % 2 == p) ans = (ans + F[i][j][n]) % Mod;
    }
  printf("%I64d\n", ans);
  return 0;
}
