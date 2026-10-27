#include <bits/stdc++.h>
using namespace std;
long long sum(long long n) { return (n * (n + 1)) / 2; }
long long ds(long long s, long long e) {
  if (s <= 1) return sum(e);
  return sum(e) - sum(s - 1);
}
long long bs(long long n, long long k) {
  long long st = 1, en = k;
  while (st < en) {
    long long mid = (st + en) / 2;
    long long sub = ds(mid, k);
    if (sub == n)
      return k - mid + 1;
    else if (sub > n)
      st = mid + 1;
    else
      en = mid;
  }
  return k - st + 2;
}
int main() {
  long long n, k;
  cin >> n >> k;
  if (n == 1)
    cout << "0" << endl;
  else if (n <= k)
    cout << "1";
  else {
    k--;
    n--;
    if (sum(k) < n)
      cout << "-1" << endl;
    else
      cout << bs(n, k);
  }
}
