#include <bits/stdc++.h>
using namespace std;
int n;
int a[100500];
int sum;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  if (sum % n == 0) {
    printf("%d", n);
    return 0;
  }
  printf("%d", n - 1);
  return 0;
}
