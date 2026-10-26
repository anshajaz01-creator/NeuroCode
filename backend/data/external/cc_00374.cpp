#include <bits/stdc++.h>
using namespace std;
int k, cs[100005];
string n;
int main() {
  int sum = 0;
  cin >> k >> n;
  for (int i = 0; i <= n.size() - 1; i++) {
    sum = sum + (n[i] - '0');
    cs[i + 1] = n[i] - '0';
  }
  if (sum < k) sort(cs, cs + n.size() + 1);
  if (sum >= k) {
    cout << 0;
    return 0;
  }
  int d = 0, i = 1;
  while (i <= n.size() && sum != k) {
    d++;
    while (cs[i] < 9 && sum != k) {
      cs[i]++;
      sum++;
    }
    i++;
  }
  cout << d;
}
