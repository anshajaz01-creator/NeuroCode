#include <bits/stdc++.h>
using namespace std;
int m, n;
int main() {
  int k, t, tests;
  long long int a, b, c, d;
  cin >> a;
  long long int arr[a + 10];
  long long int ans = 0;
  for (int i = 1; i <= a; i++) {
    cin >> arr[i];
  }
  ans = 0;
  arr[0] = 0;
  for (int i = 1; i <= a; i++) {
    ans += arr[i] + (i - 1) * (arr[i] - 1);
  }
  cout << ans << endl;
  return 0;
}
