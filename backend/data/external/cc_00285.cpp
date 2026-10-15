#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1000 + 10;
pair<int, int> a[MAX_N];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i + 1;
  }
  sort(a, a + n);
  if (a[0].first == a[n - 1].first) {
    cout << "Exemplary pages.\n";
    return 0;
  }
  if ((n > 2 && a[1].first == a[n - 1].first) ||
      (n > 2 && a[0].first == a[n - 2].first) ||
      (n > 2 && a[1].first != a[n - 2].first) ||
      (a[n - 1].first - a[0].first) % 2 == 1 ||
      (n > 2 &&
       ((a[n - 1].first - a[0].first) / 2) + a[0].first != a[1].first)) {
    cout << "Unrecoverable configuration.\n";
    return 0;
  }
  cout << (a[n - 1].first - a[0].first) / 2 << " ml. from cup #" << a[0].second
       << " to cup #" << a[n - 1].second << "." << endl;
  return 0;
}
