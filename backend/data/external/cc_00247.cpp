#include <bits/stdc++.h>
int n, a[200005], res;
int main() {
  int p = 0, l = 1, delta, sp = 0;
  double curdelta;
  bool single = true;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  while (a[p] == -1 && p < n) p++;
  while (p < n) {
    while (p + l < n && a[p + l] == -1) {
      if (!single && a[p] + (long long)delta * l <= 0) break;
      l++;
    }
    if (p + l == n) break;
    if (!single && a[p] + (long long)delta * l <= 0) {
      res++;
      single = true;
      p += l;
      sp = p;
      l = 1;
      while (a[p] == -1 && p < n) p++;
      continue;
    }
    curdelta = (double)(a[p + l] - a[p]) / l;
    if (single) {
      if (curdelta > 0)
        delta = curdelta + 0.00000001;
      else
        delta = curdelta - 0.00000001;
      single = false;
      if (sp != p) {
        if (a[p] - (long long)delta * (p - sp) <= 0) {
          res++;
          single = true;
          p += l;
          sp = p;
          l = 1;
          continue;
        }
      }
    }
    if (delta < curdelta - 0.00000001 || delta > curdelta + 0.00000001) {
      res++;
      single = true;
      p += l;
      sp = p;
      l = 1;
      while (a[p] == -1 && p < n) p++;
      continue;
    }
    l++;
  }
  res++;
  printf("%d", res);
  return 0;
}
