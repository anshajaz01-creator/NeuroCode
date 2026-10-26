#include <bits/stdc++.h>
using namespace std;
const int N = 100 * 1000;
const long long MOD = 1000000007;
long long n, k, sum, a[N];
void readInput() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
}
void solve() {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n; j++) {
      k = pow(2, (int)log2(n - 1) - j) + i;
      if (k < n) {
        a[k] += a[i];
        break;
      }
    }
    sum += a[i];
    a[i] = 0;
    cout << sum << endl;
  }
}
void printOutput() {}
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  readInput();
  solve();
  printOutput();
  return 0;
}
