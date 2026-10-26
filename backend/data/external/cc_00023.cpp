#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  for (; b; a %= b, swap(a, b))
    ;
  return a;
}
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  long long n, m;
  cin >> n >> m;
  vector<long long> a(n);
  set<pair<long long, long long> > st;
  for (long long i = 0; i < n; i++) cin >> a[i];
  long long last = a[n - 1];
  for (long long i = 0; i < m; i++) {
    long long x, y;
    cin >> x >> y;
    st.insert({x, y});
  }
  long long ans = 0;
  for (long long i = n - 2; i >= 0; i--) {
    bool flag = false;
    long long j = i;
    while (j <= n - 2 && st.count({a[j], a[j + 1]}) && !flag) {
      if (a[j + 1] == last) flag = true;
      swap(a[j], a[j + 1]);
      j++;
    }
    if (flag) ans++;
  }
  cout << ans;
}
