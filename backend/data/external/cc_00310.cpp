#include <bits/stdc++.h>
using namespace std;
int a[10];
inline long long unsigned turn(string s) {
  long long unsigned ans = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    ans *= 10;
    ans += s[i] - '0';
  }
  return ans;
}
int main() {
  long long unsigned k, f, t;
  string s;
  cin >> k >> s;
  f = turn(s);
  if (k == f && !f && s.size() == 1) {
    cout << "OK" << endl;
    return 0;
  }
  if (s[0] == '0') {
    cout << "WRONG_ANSWER" << endl;
    return 0;
  }
  while (k) {
    a[k % 10]++;
    k /= 10;
  }
  int i = 1;
  while (!a[i]) i++;
  t = i;
  a[i]--;
  for (i = 0; i < 10; i++)
    while (a[i]) {
      t *= 10;
      t += i;
      a[i]--;
    }
  if (t == f)
    cout << "OK" << endl;
  else
    cout << "WRONG_ANSWER" << endl;
  return 0;
}
