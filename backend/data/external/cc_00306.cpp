#include <bits/stdc++.h>
using namespace std;
int n, k;
string s;
map<int, int> vis;
queue<int> q;
void solve() {
  int n, m, d;
  cin >> n >> m >> d;
  int c[m];
  for (int i = 0; i < m; i++) cin >> c[i];
  int cur = d;
  int i = 0;
  vector<int> ans(n + 1, 0);
  int mm = m;
  bool mid = false;
  while (cur <= n) {
    if (i == m) {
      cout << "NO" << '\n';
      return;
    }
    int co = c[i];
    for (int j = cur; j < cur + c[i] && j <= n; j++, co--) {
      ans[j] = i + 1;
    }
    if (co > 0) {
      mid = true;
      mm = i + 1;
    }
    cur += (d + c[i] - 1);
    i++;
  }
  if (!mid) mm = i + 1;
  if (ans[n] == 0)
    for (i = n; i >= 0; i--) {
      if (ans[i] == 0) continue;
      if (ans[i] == m) {
        cout << "YES\n";
        for (int i = 1; i < n + 1; i++) cout << ans[i] << ' ';
        return;
      }
      if (ans[i] != m) break;
    }
  i = n;
  int last = n;
  for (int j = m; j >= mm; j--) {
    for (int co = c[j - 1]; last > 0 && co > 0; last--, co--) {
      if (ans[last] != 0) {
        mm = min(mm, ans[last]);
      }
      ans[last] = j;
    }
  }
  cout << "YES\n";
  for (int i = 1; i < n + 1; i++) cout << ans[i] << ' ';
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
