#include <bits/stdc++.h>
using namespace std;
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long n, V;
  cin >> n >> V;
  long long arr[n];
  for (long long i = 0; i < n; i++) cin >> arr[i];
  long long b[n];
  for (long long i = 0; i < n; i++) {
    cin >> b[i];
  }
  double store = double(10000000000);
  for (long long i = 0; i < n; i++) {
    double curr = (double(b[i]) / double(arr[i]));
    store = min(curr, store);
  }
  double sum = 0.0000;
  for (long long i = 0; i < n; i++) {
    sum += (arr[i] * store);
    if (sum > double(V)) {
      sum = double(V);
      break;
    }
  }
  cout << setprecision(5) << sum << "\n";
}
