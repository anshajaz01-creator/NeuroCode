#include <bits/stdc++.h>
#pragma gcc optimize("O3")
#pragma gcc optimize("Ofast")
using namespace std;
int n;
pair<int, int> a[1005];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    int f = 0;
    for (int i = 1; i < n; i++) {
      if (a[i].second > a[i + 1].second) {
        f = 1;
        cout << "NO\n";
        break;
      }
    }
    if (f) continue;
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
      for (int j = a[i].first; j < a[i + 1].first; j++) cout << 'R';
      for (int j = a[i].second; j < a[i + 1].second; j++) cout << 'U';
    }
    cout << '\n';
  }
  return 0;
}
