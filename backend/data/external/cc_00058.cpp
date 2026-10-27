#include <bits/stdc++.h>
using namespace std;
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  long long t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    long long ar[n];
    for (__typeof(n) i = (0) - ((0) > (n)); i != (n) - ((0) > (n));
         i += 1 - 2 * ((0) > (n)))
      cin >> ar[i];
    long long pre[n], suf[n];
    long long flag = 0;
    pre[0] = 1;
    suf[n - 1] = 1;
    for (__typeof(n) i = (1) - ((1) > (n)); i != (n) - ((1) > (n));
         i += 1 - 2 * ((1) > (n))) {
      pre[i] = (pre[i - 1] && (ar[i] >= i));
    }
    for (long long i = n - 2; i >= 0; i--)
      suf[i] = (suf[i + 1] && (ar[i] >= (n - 1 - i)));
    for (__typeof(n) i = (0) - ((0) > (n)); i != (n) - ((0) > (n));
         i += 1 - 2 * ((0) > (n))) {
      if (pre[i] == 1 && suf[i] == 1) {
        cout << "Yes" << '\n';
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      cout << "No" << '\n';
    }
  }
  return 0;
}
