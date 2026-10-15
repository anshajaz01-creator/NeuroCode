#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
int a[N];
bool st[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    if (st[i]) continue;
    st[i] = 1;
    ++res;
    int last = a[i];
    for (int j = i + 1; j <= n; ++j) {
      if (!st[j] && a[j] > last) {
        last = a[j];
        st[j] = 1;
      }
    }
  }
  printf("%d\n", res);
  return 0;
}
