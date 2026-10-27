#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  long long res = 0;
  map<int, int> qu, a;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];
  int l = 1, r = 1;
  qu[a[1]] = 1;
  while (r <= n) {
    if (qu[a[r]] < k) {
      r++;
      qu[a[r]]++;
    } else {
      res += n - r + 1;
      qu[a[l]]--;
      l++;
    }
  }
  cout << res;
}
