#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
int n, p[N], s1, s2, s3;
void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &p[i]), s1 = (p[i] == p[1] ? i : s1);
  int pos = s1 * 2 + 1;
  s2 = pos;
  for (int i = pos; i <= n; i++) s2 = (p[i] == p[pos] ? i : s2);
  pos = s2 + s1 + 1;
  s3 = pos;
  for (int i = pos; i <= n; i++) s3 = (p[i] == p[pos] ? i : s3);
  if (s3 > n / 2) return puts("0 0 0"), void();
  pos = s3 + 1;
  int q = p[n / 2 + 1];
  for (int i = s3; i <= n; i++)
    if (p[i] > q) s3 = i;
  printf("%d %d %d\n", s1, s2 - s1, s3 - s2);
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) solve();
}
