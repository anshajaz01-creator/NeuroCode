#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
long long powmod(long long a, long long b, long long MOD) {
  long long ans = 1;
  while (b) {
    if (b % 2) ans = ans * a % MOD;
    a = a * a % MOD;
    b /= 2;
  }
  return ans;
}
const int N = 2e5 + 11;
int n, d;
int s[N], p[N];
vector<int> v;
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> d;
  for (int i = 1; i <= n; i++) cin >> s[i];
  for (int i = 1; i <= n; i++) cin >> p[i];
  s[d] += p[1];
  priority_queue<int> v;
  for (int i = 2; i <= n; i++) v.push(p[i]);
  for (int i = d - 1; i >= 1; i--) {
    if (s[i] > s[d]) return cout << i + 1, 0;
    while (!v.empty() && v.top() + s[i] > s[d]) v.pop();
    if (v.empty()) return cout << i + 1, 0;
    v.pop();
  }
  cout << 1;
  return 0;
}
