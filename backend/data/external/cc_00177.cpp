#include <bits/stdc++.h>
using namespace std;
unsigned long long min(unsigned long long x, unsigned long long y) {
  if (x < y) return x;
  return y;
}
unsigned long long max(unsigned long long x, unsigned long long y) {
  if (x < y) return y;
  return x;
}
long long min(long long x, long long y) {
  if (x < y) return x;
  return y;
}
long long max(long long x, long long y) {
  if (x < y) return y;
  return x;
}
double min(double x, double y) {
  if (x < y) return x;
  return y;
}
double max(double x, double y) {
  if (x < y) return y;
  return x;
}
unsigned long long gcd(unsigned long long x, unsigned long long y) {
  if (!x) return y;
  if (!y) return x;
  if (x > y) swap(x, y);
  return gcd(x, y % x);
}
unsigned long long inv(unsigned long long a, unsigned long long c) {
  if (a == 1) {
    return 1;
  }
  return ((c - (c / a)) * inv(c % a, c)) % c;
}
long long k, d, t;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> k >> d >> t;
  k <<= 1;
  d <<= 1;
  t <<= 1;
  long long timeOn = d * ((k + d - 1) / d);
  long long offCook = (timeOn - k) >> 1;
  long long total = k + offCook;
  long long q = t / total, r = t % total;
  long long ans = timeOn * q;
  if (r <= k) {
    ans += r;
  } else {
    ans += k + ((r - k) << 1);
  }
  long long res = (ans >> 1);
  string s;
  if (ans & 1) {
    s += '.';
    s += '5';
  }
  cout << res << s << "\n";
  return 0;
}
