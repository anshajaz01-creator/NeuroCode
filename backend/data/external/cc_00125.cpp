#include <bits/stdc++.h>
using namespace std;
int a[100010];
int coef[100010];
int bitcnt[100010];
long long ans[100010];
int main(void) {
  int N, i, j, K;
  scanf("%d", &N);
  for ((i) = 0; (i) < (int)(N); (i)++) scanf("%d", &a[i]);
  for ((i) = 0; (i) < (int)(N); (i)++) bitcnt[i] = __builtin_popcount(i);
  for ((i) = 0; (i) < (int)(N - 1); (i)++) coef[i] = bitcnt[N - 1 - i];
  for (K = N - 1; K >= 1; K--) {
    for ((i) = 0; (i) < (int)(K); (i)++) coef[i] = min(coef[i], bitcnt[K - i]);
    for ((i) = 0; (i) < (int)(K); (i)++) ans[K] += (long long)coef[i] * a[i];
  }
  for (i = 1; i < N; i++) cout << ans[i] << endl;
  return 0;
}
