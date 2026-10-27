#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, i;
  vector<int> v;
  scanf("%d", &n);
  v.resize(n);
  for (i = 0; i < n; i++) scanf("%d", &v[i]);
  sort(v.begin(), v.end());
  int max = 1, cnt = 1;
  for (i = 0; i < n - 1; i++) {
    if (v[i] == v[i + 1])
      cnt++;
    else
      cnt = 1;
    if (cnt > max) max = cnt;
  }
  printf("%d", max);
  return 0;
}
