#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
long long s[N];
int main() {
  int n;
  long long a, b, sum;
  cin >> n >> a >> b;
  sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    sum += s[i];
  }
  sort(s + 2, s + n + 1);
  for (int p = n; p >= 2; p--) {
    if (a * s[1] >= b * sum) {
      cout << n - p << endl;
      return 0;
    }
    sum -= s[p];
  }
  cout << n - 1 << endl;
  return 0;
}
