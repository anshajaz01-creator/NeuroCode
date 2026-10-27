#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int a[105];
    int has[105] = {0};
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      has[a[i]]++;
    }
    int m1 = 0;
    int m2 = 0;
    for (int i = 0; i <= 100; i++) {
      if (m1 == i && has[i] >= 1) {
        if (has[i] >= 2 && m1 == m2) {
          m1++;
          m2++;
        } else {
          m1++;
        }
        continue;
      }
      break;
    }
    printf("%d\n", m1 + m2);
  }
  return 0;
}
