#include <bits/stdc++.h>
using namespace std;
int po(long long &a) {
  int ret = -1;
  while (a) {
    a = a >> 1;
    ret++;
  }
  return ret;
}
pair<long long, long long> val[33];
int main() {
  val[0].second = 1;
  long long temp = 1, res = 0;
  for (int i = 1; i <= 32; i++) val[i].second = temp * 2, temp *= 2;
  int n, q;
  scanf("%d %d", &n, &q);
  while (n--) {
    long long c;
    scanf("%lld", &c);
    int t = po(c);
    val[t].first++;
  }
  while (q--) {
    long long bj;
    res = 0;
    scanf("%lld", &bj);
    for (int i = 31; i >= 0; i--) {
      temp = bj / val[i].second;
      temp = min(temp, val[i].first);
      res += temp;
      bj -= (temp * val[i].second);
    }
    if (bj != 0)
      printf("%d\n", -1);
    else
      cout << res << endl;
  }
  return 0;
  ;
}
