#include <bits/stdc++.h>
using namespace std;
long long n, m, k;
string s, t, p;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m >> k;
  long long a[m];
  for (long long i = 0; i <= m - 1; i++) {
    cin >> a[i];
  }
  long long ans = 1;
  long long end;
  if (a[0] % k != 0)
    end = ((a[0] / k) + 1) * k;
  else
    end = a[0];
  long long er = 0;
  for (long long i = 0; i <= m - 1; i++) {
    if (a[i] <= end) {
      er++;
    } else {
      ans++;
      end = end + er;
      long long ml = 0;
      if (end < a[i]) ml = (a[i] - end) / k - 1;
      end = end + k * ml;
      while (end < a[i]) end = end + k;
      er = 1;
    }
  }
  cout << ans << endl;
}
