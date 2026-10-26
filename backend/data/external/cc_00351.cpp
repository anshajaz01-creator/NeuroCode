#include <bits/stdc++.h>
int main() {
  unsigned long long int x, y, z, c = 0, r, d = 0;
  scanf("%llu %llu %llu", &x, &y, &z);
  c = c + (x / z) + (y / z);
  r = x % z + y % z;
  if (r >= z) {
    r = r / z;
    c = c + r;
    if (x % z != 0 && y % z != 0) {
      if (x % z > y % z) {
        d = z - x % z;
      } else {
        d = z - y % z;
      }
    } else {
      d = 0;
    }
  } else {
    d = 0;
  }
  printf("%llu %llu", c, d);
  return 0;
}
