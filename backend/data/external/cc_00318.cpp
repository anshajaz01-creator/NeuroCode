#include <bits/stdc++.h>
using namespace std;
void Test() {
  long long n;
  cin >> n;
  long long a[n], b[n];
  for (long long i = 0; i < n; i++) {
    cin >> a[i];
    b[i] = a[i];
  }
  sort(b, b + n);
  long long cnt = 0;
  for (long long i = 0; i < n; i++) {
    if (a[i] != b[i]) ++cnt;
  }
  if (!cnt || cnt == 2)
    cout << "YES";
  else
    cout << "NO";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(10);
  Test();
  return 0;
}
