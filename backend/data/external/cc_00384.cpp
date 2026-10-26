#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<long long> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  long long count = a[1];
  for (int i = 2; i <= n; ++i) {
    count += i * (a[i] - 1) + 1;
  }
  cout << count;
  return 0;
}
