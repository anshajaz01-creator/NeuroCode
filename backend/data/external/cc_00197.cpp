#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
void solve() {
  long long int n, m, k;
  cin >> n >> m >> k;
  vector<long long int> a(m), pos(m);
  long long int i;
  for (i = 0; i <= m - 1; i++) cin >> a[i];
  pos[0] = (a[0] - 1) / k + 1;
  long long int del = 0, cnt = 1, c = 0;
  for (i = 1; i <= m - 1; i++) {
    pos[i] = (a[i] - 1 - del) / k + 1;
    if (pos[i] != pos[i - 1]) {
      del += cnt;
      cnt = 0;
      c++;
      pos[i] = (a[i] - 1 - del) / k + 1;
    }
    cnt++;
  }
  cout << c + 1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(10);
  auto start = high_resolution_clock::now();
  int i, t = 1;
  for (i = 1; i <= t; i++) solve();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
}
