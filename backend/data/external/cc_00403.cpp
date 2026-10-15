#include <bits/stdc++.h>
using namespace std;
void resolve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  if (n == 1) {
    cout << "yes\n";
    cout << 1 << " " << 1 << endl;
    return;
  }
  int l = 0;
  while (l + 1 < n && a[l] < a[l + 1]) l++;
  int r = l + 1;
  while (r < n && a[r] < a[r - 1]) r++;
  reverse(a.begin() + l, a.begin() + r);
  for (int i = 1; i < n; i++) {
    if (a[i] < a[i - 1]) {
      cout << "no\n";
      return;
    }
  }
  cout << "yes\n";
  cout << l + 1 << " " << r << endl;
}
int main() {
  int t;
  t = 1;
  while (t--) {
    resolve();
  }
}
