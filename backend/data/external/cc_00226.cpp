#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int main() {
  int n;
  float V;
  cin >> n >> V;
  float a[n], b[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  float lmt = inf;
  for (int i = 0; i < n; i++) {
    lmt = min(lmt, b[i] / a[i]);
  }
  float ma = 0;
  for (int i = 0; i < n; i++) ma += lmt * a[i];
  cout << min(ma, V) << "\n";
  return 0;
}
