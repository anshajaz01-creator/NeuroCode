#include <bits/stdc++.h>
using namespace std;
int main() {
  int i;
  int x, y;
  int a[100000];
  scanf("%d%d", &x, &y);
  if (x == y) {
    printf("%d", x);
    return 0;
  }
  if (x % 2 == 0) {
    printf("2");
    return 0;
  } else if (x % 3 == 0) {
    if (y - x <= 4) {
      printf("3");
    } else {
      printf("2");
    }
  } else {
    printf("2");
  }
  return 0;
}
