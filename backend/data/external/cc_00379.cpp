#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, num = 0;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    if (i == 0)
      printf("%d", (num + a) / m);
    else
      printf(" %d", (num + a) / m);
    num = (num + a) % m;
  }
  return 0;
}
