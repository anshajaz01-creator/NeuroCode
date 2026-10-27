#include <bits/stdc++.h>
int Count(int l, int r) {
  if (l == r) {
    return l;
  }
  return 2;
}
int main() {
  int l, r;
  std::cin >> l >> r;
  std::cout << Count(l, r) << std::endl;
  return 0;
}
