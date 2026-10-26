#include <bits/stdc++.h>
using namespace std;
struct node {
  int x, y;
} a[10010];
bool cmp(node aa, node bb) { return aa.x < bb.x; }
int main() {
  int n;
  long long sum = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i].x);
    sum += a[i].x;
    a[i].y = i;
  }
  sort(a, a + n, cmp);
  int flag = 1;
  for (int i = 1; i < n - 2; ++i) {
    if (a[i].x != a[i + 1].x) {
      flag = 0;
      break;
    }
  }
  if (flag && sum % n == 0 && sum / n * 2 == a[0].x + a[n - 1].x) {
    if (a[0].x == a[n - 1].x)
      printf("Exemplary pages.");
    else
      printf("%d ml. from cup #%d to cup #%d.", (a[n - 1].x - a[0].x) / 2,
             a[0].y + 1, a[n - 1].y + 1);
  } else
    printf("Unrecoverable configuration.");
  return 0;
}
