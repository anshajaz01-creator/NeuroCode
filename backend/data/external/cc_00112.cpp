#include <bits/stdc++.h>
using namespace std;
long long n;
long long m;
bool isSmall(string &a, string &b) {
  if (a == b) return false;
  for (int i = 0; i < min(n, m); i++) {
    if (a[i] > b[i])
      return false;
    else if (a[i] < b[i])
      return true;
  }
  if (n > m) return false;
  return true;
}
void solve(int c) {
  string a, b;
  cin >> a >> b;
  n = a.size(), m = b.size();
  for (int i = 0; i < n; i++) {
    char small = 'Z';
    int idx = -1;
    for (int j = i + 1; j < n; j++) {
      if (a[j] <= small) {
        small = a[j];
        idx = j;
      }
    }
    if (small < a[i] && idx > -1) {
      swap(a[i], a[idx]);
      break;
    }
  }
  if (isSmall(a, b)) {
    cout << a << '\n';
  } else
    cout << "---" << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long t = 1;
  cin >> t;
  int c = 1;
  while (t--) {
    solve(c);
    c++;
  }
}
