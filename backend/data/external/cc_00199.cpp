#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, m, k;
  cin >> n >> m >> k;
  vector<long long int> p(m);
  for (int i = 0; i < m; i++) {
    cin >> p[i];
  }
  long long int ans = 0;
  long long int cnt = 0;
  for (int i = 0; i < m; i++) {
    long long int dif = cnt % k;
    long long int cp = p[i];
    int cnt1 = 0;
    while (p[i + 1] - dif <= (cp - dif + k - 1) / k * k && i < m) {
      i++;
      cnt1++;
    }
    cnt += (cnt1 + 1);
    ans++;
  }
  cout << ans << endl;
}
