#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  long long n, k;
  cin >> n >> k;
  k <<= 1;
  long long d[n];
  for (int i = 0; i < n; ++i) {
    cin >> d[i];
  }
  sort(d, d + n);
  int it = 0;
  int cnt = 0;
  while (it < n) {
    while (it < n and k >= d[it]) k = max(k, d[it++] << 1);
    if (it < n) {
      k <<= 1;
      cnt++;
    }
  }
  cout << cnt << endl;
}
