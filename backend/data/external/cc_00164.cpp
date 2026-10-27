#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, sa = 0, sg = 0, i, cnt = 0;
  cin >> n;
  long long int a, g;
  for (i = 0; i < n; ++i) {
    scanf("%lld %lld", &a, &g);
    if (abs(sa + a - sg) <= 500) {
      sa += a;
      printf("A");
    } else {
      sg += g;
      printf("G");
    }
  }
  return 0;
}
