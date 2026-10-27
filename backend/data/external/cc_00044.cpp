#include <bits/stdc++.h>
using namespace std;
int main() {
  int x, y;
  cin >> x >> y;
  int i = x;
  int j = 2;
  i = x;
  int n = 2;
  int start;
  int rem;
  int prev_count = 1;
  int count = 1;
  int maxnum = n;
  while (n <= y) {
    if (y - x == 0) {
      maxnum = x;
      break;
    }
    rem = x % n;
    if (rem == n) break;
    if (rem != 0) {
      start = n - rem + x;
      j = start;
    } else
      j = x;
    prev_count = count;
    count = 0;
    while (j <= y) {
      count++;
      j = j + n;
    }
    if (prev_count > count)
      break;
    else if (count >= prev_count)
      maxnum = n;
    n = n + 1;
  }
  cout << maxnum << endl;
  return 0;
}
