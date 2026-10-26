#include <bits/stdc++.h>
using namespace std;
bool ara[1000006];
int main() {
  int n, cnt, a, b;
  while (cin >> n) {
    cnt = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &a, &b);
      if (cnt + a <= 500)
        ara[i] = 0, cnt += a;
      else
        ara[i] = 1, cnt -= b;
    }
    for (int i = 0; i < n; i++) {
      if (!ara[i])
        printf("A");
      else
        printf("G");
    }
    printf("\n");
  }
  return 0;
}
