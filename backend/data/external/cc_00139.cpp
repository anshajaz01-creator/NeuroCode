#include <bits/stdc++.h>
long long cnt1, cnt2, x, y;
long long max = 3000000007;
int judge(long long n) {
  long long num1 = n / x;
  long long num2 = n / y;
  long long numsum = n / x / y;
  long long num = num1 + num2 - numsum;
  long long cangivea = num - num1;
  long long cangiveb = num - num2;
  if (((cnt1 - cangivea) > 0 ? (cnt1 - cangivea) : 0) +
          ((cnt2 - cangiveb) > 0 ? (cnt2 - cangiveb) : 0) <=
      n - num)
    return 1;
  else
    return 0;
}
long long search(long low, long long high) {
  if (low >= high) {
    if (judge(low))
      return low;
    else {
      printf("11\n");
      return -1;
    }
  } else if (low + 1 == high) {
    if (judge(low))
      return low;
    else if (judge(high))
      return high;
    else {
      printf("1\n");
      return -1;
    }
  } else {
    long long mid = (low + high) / 2;
    if (judge(mid))
      return search(low, mid);
    else
      return search(mid, high);
  }
}
int main() {
  scanf("%I64d %I64d %I64d %I64d", &cnt1, &cnt2, &x, &y);
  printf("%I64d\n", search(0, max));
  return 0;
}
