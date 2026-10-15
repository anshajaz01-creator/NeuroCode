#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;
int main(int argc, const char* argv[]) {
  int n;
  scanf(" %d", &n);
  int a;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    scanf(" %d", &a);
    sum += a;
  }
  if (sum % n == 0) {
    printf("%d\n", n);
  } else {
    printf("%d\n", n - 1);
  }
  return 0;
}
