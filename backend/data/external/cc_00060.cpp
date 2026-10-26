#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
const int mod = 998244353;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int n, a[maxn], b[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i];
    int ff = 0;
    for (int i = 1; i < n; i++) {
      b[i + 1] = min(b[i + 1], b[i] - 1);
      if (b[i + 1] < 0) {
        ff = 1;
        break;
      }
    }
    if (!ff) {
      cout << "Yes" << '\n';
      continue;
    }
    a[0] = -1;
    int pos = -1;
    for (int i = 1; i < n; i++) {
      int temp = a[i];
      a[i] = min(a[i], a[i - 1] + 1);
      if (a[i] >= a[i + 1]) {
        a[i] = temp;
        pos = i;
        break;
      }
    }
    if (pos == -1) {
      cout << "Yes" << '\n';
      continue;
    }
    int flag = 0;
    for (int i = pos; i < n; i++) {
      a[i + 1] = min(a[i + 1], a[i] - 1);
      if (a[i + 1] < 0) {
        flag = 1;
        break;
      }
    }
    if (flag)
      cout << "No" << '\n';
    else
      cout << "Yes" << '\n';
  }
  return 0;
}
