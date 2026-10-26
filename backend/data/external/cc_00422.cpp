#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, r1, ans = 0;
  cin >> n;
  r1 = (n * 2) - 1;
  ans += r1;
  for (int i = r1 - 2; i > 0; i -= 2) {
    ans += 2 * i;
  }
  cout << ans << endl;
  return 0;
}
