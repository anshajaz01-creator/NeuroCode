#include <bits/stdc++.h>
const int maxn = 1e5 + 10;
int n, m;
int a[maxn], b[maxn], L[maxn], R[maxn];
int s[200010], f[maxn], g[maxn];
inline int sum(int a, int b) { return s[b] - s[a - 1]; }
inline int sum(int a) { return s[a] - s[a - 1]; }
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = 1; i <= m; ++i) std::cin >> b[i], ++s[b[i]];
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + m + 1);
  a[0] = -20040826, a[n + 1] = 20040826;
  for (int i = 1; i <= 200000; ++i) s[i] += s[i - 1];
  for (int i = 1; i <= n; ++i)
    if (a[i] != a[i - 1] + 1)
      L[i] = i;
    else
      L[i] = L[i - 1];
  for (int i = n; i; --i)
    if (a[i] != a[i + 1] - 1)
      R[i] = i;
    else
      R[i] = R[i + 1];
  for (int i = 1; i <= n; ++i) {
    (f[i] = std::max(f[i], std::max(f[i - 1], g[i - 1]) + sum(a[i])));
    (g[i] = std::max(g[i], std::max(f[i - 1], g[i - 1]) + sum(a[i])));
    (f[i] = std::max(f[i], g[i]));
    for (int j = 1, len; j <= m && b[j] <= a[i]; ++j)
      if ((len = a[i] - b[j] + 1) <= i)
        (g[i] = std::max(g[i], f[L[i - len + 1] - 1] + sum(b[j], a[i])));
    (f[i] = std::max(f[i], g[i]));
    for (int j = m, len; j && b[j] >= a[i]; --j)
      if ((len = b[j] - a[i] + 1) <= n - i + 1)
        (f[R[i + len - 1]] =
             std::max(f[R[i + len - 1]], g[i] + sum(a[i] + 1, b[j])));
  }
  std::cout << f[n] << '\n';
}
