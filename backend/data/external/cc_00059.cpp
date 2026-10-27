#include <bits/stdc++.h>
using namespace std;
int a[300005], n;
bool ch1() {
  for (int i = 0; i < n; i++) {
    if (a[i] < i) return 0;
  }
  return 1;
}
bool ch2() {
  for (int i = 0; i < n; i++) {
    if (a[i] < n - 1 - i) return 0;
  }
  return 1;
}
bool ch3() {
  int pos = 0;
  for (; pos < n; pos++) {
    if (a[pos] < pos) break;
  }
  pos--;
  int pos1 = n - 1;
  for (; pos1 >= 0; pos1--) {
    if (a[pos1] < n - 1 - pos1) break;
  }
  pos1++;
  return pos >= pos1;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    if (ch1() || ch2() || ch3())
      cout << "Yes" << '\n';
    else
      cout << "No" << '\n';
  }
  return 0;
}
