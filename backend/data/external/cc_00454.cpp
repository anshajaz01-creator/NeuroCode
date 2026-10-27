#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, p;
  cin >> n >> p;
  vector<int> a(n, 0), b(n, 0);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  int res = 1;
  int win = a[p - 1] + b[0];
  vector<int> v(n, 0);
  for (int i = 0; i < n; i++) {
    if (i != p - 1) {
      int esq = 1, dir = n - 1, r = -1;
      while (esq <= dir) {
        int mid = (esq + dir) / 2;
        if (b[mid] + a[i] <= win) r = mid;
        if (b[mid] + a[i] <= win)
          dir = mid - 1;
        else
          esq = mid + 1;
      }
      if (r == -1)
        res++;
      else
        v[r]++;
    }
  }
  for (int i = 1; i < n - 1; i++) {
    if (v[i] > 1) {
      v[i + 1] += v[i] - 1;
      v[i] = 1;
    }
  }
  if (v.back() > 1) res += v.back() - 1;
  cout << res << endl;
}
