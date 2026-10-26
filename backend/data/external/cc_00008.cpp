#include <bits/stdc++.h>
using namespace std;
const int N = 105, mod = 1000000007;

int n, m, x, b[N], c[N], l, r, ans, f[N][N * N];
 
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
  for (int i = 1; i < n; i++) scanf("%d", &b[i]);
  scanf("%d%d", &m, &x), f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    l = i * x, r += c[i];
    for (int j = 1; j <= i; j++) l += b[j] * (i - j);
    for (int j = r; j >= max(l, 0); j--) {
      for (int k = 0; k <= min(c[i], j); k++) {
        f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;
      }
    }
  } for (int i = 0; i <= r; i++) (ans += f[n][i]) %= mod;
	printf("%d\n",ans);
}