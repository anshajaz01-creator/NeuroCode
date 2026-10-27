#include <bits/stdc++.h>
using namespace std;
const char *fin = "";
const char *fon = "";
const int OO = (int)(1e9 + 7);
const int MAXN = (int)(1);
long long k, d, t, y;
double A, B;
bool Check(long long x) {
  double tmp = x * (A + B);
  return tmp - 1 >= 0 || tmp + A - 1 >= 0;
}
void Inp() {
  cin >> k >> d >> t;
  y = (k >= d ? d * (k / d) + (k % d != 0) * d - k : d - k);
  A = 1.0 * k / t;
  B = 1.0 * y / (2 * t);
  long long lo = 0, hi = 1LL * OO * OO, mid = (lo + hi) / 2;
  for (int i = 1; i <= 100; ++i) {
    if (Check(mid))
      hi = mid;
    else
      lo = mid;
    mid = (lo + hi) / 2;
  }
  cout << fixed;
  cout << setprecision(10);
  for (long long i = lo; i <= hi; ++i) {
    if (Check(i)) {
      double res = 1.0 * i * (k + y);
      double tmp = i * (A + B);
      if (tmp < 1) res += 1.0 * (1 - tmp) * t;
      if (tmp > 1) res -= 1.0 * (tmp - 1) * 2 * t;
      cout << res;
      break;
    }
  }
}
int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  Inp();
  return 0;
}
