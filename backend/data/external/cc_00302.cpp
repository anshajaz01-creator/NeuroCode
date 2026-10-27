#include <bits/stdc++.h>
using namespace std;
long long int power(long long int x, unsigned long long int y) {
  long long int res = 1;
  while (y > 0) {
    if (y & 1) {
      res = res * x;
    }
    y = y >> 1;
    x = x * x;
  }
  return res;
}
long long int powermod(long long int x, unsigned long long int y,
                       long long int p) {
  long long int res = 1;
  x = x % p;
  while (y > 0) {
    if (y & 1) {
      res = (res * x) % p;
    }
    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}
int32_t main() {
  long long int n;
  cin >> n;
  vector<long long int> v;
  for (long long int i = (long long int)(0); i < (long long int)(n); i++) {
    long long int temp;
    cin >> temp;
    v.push_back(temp);
  }
  long long int l = 0, r = n - 1;
  long long int prev = 0;
  string ans = "";
  while (l <= r) {
    if (v[l] > prev && v[l] < v[r]) {
      ans += "L";
      prev = v[l];
      l++;
    } else if (v[r] > prev) {
      ans += "R";
      prev = v[r];
      r--;
    } else if (v[l] > prev) {
      ans += "L";
      prev = v[l];
      l++;
    } else
      break;
  }
  l = 0;
  r = n - 1;
  string ans2 = "";
  prev = 0;
  while (l <= r) {
    if (v[r] > prev && v[r] < v[l]) {
      ans2 += "R";
      prev = v[r];
      r--;
    } else if (v[l] > prev) {
      ans2 += "L";
      prev = v[l];
      l++;
    } else if (v[r] > prev) {
      ans2 += "R";
      prev = v[r];
      r--;
    } else
      break;
  }
  if (ans2.length() > ans.length()) ans = ans2;
  cout << ans.length() << "\n";
  cout << ans << "\n";
  return 0;
}
