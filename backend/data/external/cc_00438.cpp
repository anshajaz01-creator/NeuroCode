#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  if (a == 0 || b == 0) {
    return a + b;
  }
  if (a > b) {
    return gcd(a % b, b);
  }
  return gcd(a, b % a);
}
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }
  vector<long long> lengths;
  vector<int> used(n, 0);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    if (used[i]) {
      continue;
    }
    int cur = i;
    vector<int> nodes;
    while (!used[cur]) {
      nodes.push_back(cur);
      used[cur] = 1;
      cur = a[cur];
    }
    int ps = find(nodes.begin(), nodes.end(), cur) - nodes.begin();
    lengths.push_back(nodes.size() - ps);
    sum += lengths.back();
    if (lengths.back() % 2 == 0) {
      lengths.back() /= 2;
    }
  }
  if (sum != n) {
    cout << -1 << endl;
    return 0;
  }
  long long res = 1;
  for (auto i : lengths) {
    res = lcm(res, i);
  }
  cout << res << endl;
  return 0;
}
