#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long int n, m, k;
  cin >> n >> m >> k;
  long long int p[m];
  for (int i = 0; i < m; i++) cin >> p[i];
  long long int cnt = 0;
  long long int temp = 0;
  long long int ans = 0;
  long long int cur = -1;
  for (int i = 0; i < m; i++) {
    long long int val = (p[i] - cnt) / k;
    if ((p[i] - cnt) % k == 0) val--;
    if (val == cur) {
      temp++;
    } else {
      cnt += temp;
      val = (p[i] - cnt) / k;
      if ((p[i] - cnt) % k == 0) val--;
      temp = 1;
      cur = val;
      ans++;
    }
  }
  cout << ans;
  return 0;
}
