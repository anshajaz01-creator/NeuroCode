#include <bits/stdc++.h>
using namespace std;
char n[10000005];
long long ck[10000005];
int main() {
  long long k;
  long long tot;
  while (scanf("%lld", &k) != EOF) {
    scanf("%s", n);
    int len = strlen(n);
    tot = 0;
    for (int i = 0; i < len; i++) {
      tot += (n[i] - '0');
      ck[i] = (n[i] - '0');
    }
    sort(ck, ck + len);
    if (tot >= k)
      printf("0\n");
    else {
      long long t = k - tot;
      long long ans = 0;
      int j = 0;
      long long ca = 0;
      for (int i = 0; i < len; i++) {
        if (9 - ck[i] < t) {
          t -= (9 - ck[i]);
          ca++;
        } else {
          t -= t;
          ca++;
        }
        if (t == 0) break;
      }
      printf("%lld\n", ca);
    }
  }
  return 0;
}
