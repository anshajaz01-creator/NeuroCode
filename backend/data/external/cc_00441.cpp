#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
int n, a[maxn], vis[maxn];
long long ANS, ans, cnt;
int dfs(int u, int r) {
  cnt++;
  if (u == r) return cnt;
  if (vis[u]) return -1;
  vis[u] = 1;
  return dfs(a[u], r);
}
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  ANS = 1;
  for (int i = 1; i <= n; i++) {
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    ans = dfs(a[i], i);
    if (ans == -1) {
      ANS = -1;
      break;
    }
    if (!(ans & 1)) ans /= 2;
    ANS = lcm(ans, ANS);
  }
  printf("%I64d\n", ANS);
  return 0;
}
