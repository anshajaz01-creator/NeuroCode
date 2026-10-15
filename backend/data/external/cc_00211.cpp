#include <bits/stdc++.h>
using namespace std;
const int N = 500010, M = 30, INF = 0x3f3f3f3f;
int T;
string l[N];
long long f[M][M];
void solve() {
  long long ans = 0, n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> l[i];
  int s, e;
  for (int i = 1; i <= n; i++) {
    s = l[i][0] - 'a', e = l[i][l[i].size() - 1] - 'a';
    for (int j = 0; j < 26; j++)
      if (f[j][s]) f[j][e] = max(f[j][e], (long long)(f[j][s] + l[i].size()));
    f[s][e] = max(f[s][e], (long long)l[i].size());
  }
  for (int i = 0; i < 26; i++) ans = max(ans, f[i][i]);
  cout << ans << '\n';
}
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  while (T--) solve();
  return 0;
}
