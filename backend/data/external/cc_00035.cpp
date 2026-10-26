#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, m;
  long long a[5005][5], last = 0, b[5005] = {0};
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
  }
  int c[5005] = {0}, d[5005] = {0};
  for (int i = 1; i <= n; i++) b[i] = (long long)1e9;
  for (int i = 1; i <= m; i++) {
    if (a[i][1] == 1)
      for (int j = a[i][2]; j <= a[i][3]; j++) c[j] += a[i][4];
    else {
      for (int j = a[i][2]; j <= a[i][3]; j++) {
        b[j] = min(b[j], a[i][4] - c[j]);
      }
    }
  }
  for (int i = 1; i <= n; i++) d[i] = b[i];
  long long flag = 0;
  for (int i = 1; i <= m; i++) {
    if (a[i][1] == 1)
      for (int j = a[i][2]; j <= a[i][3]; j++) b[j] += a[i][4];
    else {
      long long Max = b[a[i][2]];
      for (int j = a[i][2]; j <= a[i][3]; j++) {
        Max = max(Max, b[j]);
      }
      if (Max != a[i][4]) flag++;
    }
  }
  for (int i = 1; i <= n; i++)
    if (abs(d[i]) > (long long)1e9) flag++;
  if (flag)
    cout << "NO";
  else {
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) cout << d[i] << " ";
  }
  return 0;
}
