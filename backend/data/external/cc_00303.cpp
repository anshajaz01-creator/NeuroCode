#include <bits/stdc++.h>
using namespace std;
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
  cout << name << " : " << arg1 << '\n';
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
  const char* comma = strchr(names + 1, ',');
  cout.write(names, comma - names) << " : " << arg1 << " | ";
  __f(comma + 1, args...);
}
const long long N = 3e5 + 7;
long long n, m, d;
long long arr[N], plank[N], pos[N], st[N];
void solve() {
  cin >> n >> m >> d;
  for (long long i = 0; i < m; i++) cin >> plank[i];
  for (long long i = 0; i < m; i++) {
    long long x = plank[i];
    if (i != 0)
      pos[i] = pos[i - 1] + x;
    else
      pos[i] = x;
    st[i] = pos[i] - plank[i] + 1;
  }
  pos[m] = n + 1;
  st[m] = n + 1;
  for (long long i = m - 1; i >= 0; i--) {
    if (st[i + 1] - d > pos[i]) {
      long long x = (st[i + 1] - d);
      pos[i] = x;
      st[i] = pos[i] - plank[i] + 1;
    }
  }
  for (long long i = 0; i < m; i++)
    for (long long j = st[i]; j < pos[i] + 1; j++) arr[j] = i + 1;
  if (st[0] > d)
    cout << "NO";
  else {
    cout << "YES" << '\n';
    for (long long i = 1; i < n + 1; i++) cout << arr[i] << " ";
  }
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long t = 1;
  while (t--) solve();
}
