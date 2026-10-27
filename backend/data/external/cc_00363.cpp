#include <bits/stdc++.h>
using namespace std;
const int M = 1000000007, BIG = 0x3f3f3f3f;
int n;
vector<int> a;
vector<long long> Process() {
  vector<long long> ans(n - 1, 0);
  for (int i = 1; i < n; i++) {
    if (i > 1) ans[i - 1] += ans[i - 2];
    for (int e = 16; e >= 0; e--) {
      const int p = (1 << e);
      const int t = i + p;
      if (t <= n) {
        ans[i - 1] += a[i];
        a[t] += a[i];
        break;
      }
    }
  }
  return ans;
}
void Output() {
  const vector<long long> ans = Process();
  for (int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin >> n) {
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    Output();
  }
  return 0;
}
