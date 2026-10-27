#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 100;
int a[MAXN], temp[MAXN], n, m;
map<int, int> s;
int solve(int x, int l, bool dir, bool fs) {
  int pos = a[x], next = 0;
  if (dir)
    next = upper_bound(a, a + n, pos + l) - a - 1;
  else
    next = lower_bound(a, a + n, pos - l) - a;
  if (next == x) {
    if (!fs)
      return x;
    else
      return solve(x, l, !dir, false);
  }
  if (!fs) l = l % (abs(a[next] - pos) * 2);
  if (l < abs(pos - a[next]))
    return solve(x, l, dir, false);
  else
    return solve(next, l - abs(pos - a[next]), !dir, false);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> temp[i], a[i] = temp[i], s[a[i]] = i + 1;
  sort(a, a + n);
  while (m--) {
    int x, l;
    cin >> x >> l;
    x--;
    x = lower_bound(a, a + n, temp[x]) - a;
    cout << s[a[solve(x, l, true, true)]] << "\n";
  }
}
