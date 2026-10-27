#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long n, i;
  long long a[200000], b[200000];
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> a[i];
    b[i] = a[i];
  }
  sort(b, b + n);
  for (i = 0; i < n; i++) {
    if (b[i] != a[i]) break;
  }
  if (i == n)
    cout << "yes" << endl << "1 1";
  else {
    long long l = i;
    for (i = l; i < n; i++) {
      if (b[i] == a[l]) break;
    }
    long long r = i;
    reverse(a + l, a + r + 1);
    for (i = 0; i < n; i++)
      if (a[i] != b[i]) break;
    if (i == n)
      cout << "yes" << endl << l + 1 << " " << r + 1;
    else
      cout << "no";
  }
  return 0;
}
