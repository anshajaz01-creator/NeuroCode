#include <bits/stdc++.h>
using namespace std;
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
template <typename T, typename V>
void __print(const pair<T, V> &x) {
  cerr << '{';
  __print(x.first);
  cerr << ',';
  __print(x.second);
  cerr << '}';
}
template <typename T>
void __print(const T &x) {
  int f = 0;
  cerr << '{';
  for (auto &i : x) cerr << (f++ ? "," : ""), __print(i);
  cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) {
  __print(t);
  if (sizeof...(v)) cerr << ", ";
  _print(v...);
}
string gh = "here";
int main() {
  long long n, k;
  cin >> n >> k;
  long long l = 1, r = k + 1;
  long long ans = 1000000000000000007;
  if (n == 1) {
    cout << 0 << '\n';
    return 0;
  }
  while (r - l > 1) {
    long long mid = (l + r) / 2;
    ;
    long long aa = (k * (k + 1)) / 2 - ((mid - 1) * (mid)) / 2 - k + mid;
    ;
    if (n == aa)
      ans = min(ans, k - mid + 1);
    else if (n - aa + 1 < mid && n - aa + 1 >= 2) {
      ans = min(ans, k - mid + 2);
    }
    if (aa > n) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (ans == 1000000000000000007) {
    cout << -1 << '\n';
  } else {
    cout << ans << '\n';
  }
  return 0;
}
