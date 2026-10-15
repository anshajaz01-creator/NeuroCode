#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  scanf("%d", &t);
  int sum = 0;
  if (t == 1) {
    sum = 1;
  } else {
    sum = t * t + ((t - 1) * (t - 1));
  }
  printf("%d\n", sum);
}
