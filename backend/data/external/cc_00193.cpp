#include <bits/stdc++.h>
using namespace std;
long long pow(long long a, long long b) {
  if (b == 0) return 1;
  return a * pow(a, b - 1);
}
long long fact(long long a) {
  if (a == 1 || a == 0) return 1;
  return a * fact(a - 1);
}
long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
vector<long long> v;
long long a[1000001], b[1000001];
long long n, m, k;
long long x, sum = 0, w = 0;
string s;
string f;
long long t;
long long ans = 0, ans2 = 0;
long long minnnnnn = 0, minn = 0;
long long maxx = 0, maxxxxxxx = 0;
bool flag = true;
long long ans1 = 0, ans3 = 0, ans4 = 0;
long long r, l;
long long c, d;
int main() {
  long long odda = 0, evena = 0, oddb = 0, evenb = 0;
  cin >> n >> m;
  for (long long i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] & 1)
      odda++;
    else
      evena++;
  }
  for (long long i = 0; i < m; ++i) {
    cin >> b[i];
    if (b[i] & 1)
      oddb++;
    else
      evenb++;
  }
  while (odda && evenb) {
    ans++;
    odda--;
    evenb--;
  }
  while (oddb && evena) {
    ans++;
    oddb--;
    evena--;
  }
  cout << ans << endl;
  return 0;
}
