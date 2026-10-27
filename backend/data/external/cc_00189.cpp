#include <bits/stdc++.h>
using namespace std;
long long p[100005];
int main() {
  ios::sync_with_stdio(false);
  long long ans = 0;
  long long n, b;
  cin >> n;
  p[2] = 0;
  for (long long i = 3; i <= n; i++) {
    b = sqrt(i);
    ans = 0;
    for (int j = 2; j <= b; j++) {
      if (i % j == 0) {
        ans += j * 4;
        if (i / j != j) ans += (i / j) * 4;
      }
    }
    p[i] = p[i - 1] + ans;
  }
  cout << p[n];
  return 0;
}
