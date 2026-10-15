#include <bits/stdc++.h>
using namespace std;
int mx[101];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, k;
  cin >> n >> m >> k;
  vector<pair<int, int> > a(n);
  for (int i = 0; i < n; i++) cin >> a[i].first;
  for (int i = 0; i < n; i++)
    cin >> a[i].second, mx[a[i].second] = max(mx[a[i].second], a[i].first);
  int ans(0);
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    x--;
    if (a[x].first != mx[a[x].second]) ans++;
  }
  cout << ans;
}
