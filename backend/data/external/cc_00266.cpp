#include <bits/stdc++.h>
using namespace std;
double x;
int N, M, ar[5005], res;
int dn[5005];
int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d %lf", &ar[i], &x);
    ar[i]--;
  }
  for (int i = 0; i < N; i++) {
    for (int j = ar[i]; j >= 0; j--) {
      dn[ar[i]] = max(dn[ar[i]], 1 + dn[j]);
    }
  }
  for (int i = 0; i < N; i++) {
    res = max(res, dn[i]);
  }
  printf("%d\n", N - res);
}
