#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a, b;
  cin >> n >> a >> b;
  int s[n], sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    sum += s[i];
  }
  if ((s[0] * a) / sum >= b)
    cout << 0;
  else {
    sort(s + 1, s + n);
    int j = n - 1, count = 0;
    while (j >= 1) {
      sum -= s[j];
      count++;
      if ((s[0] * a) / sum >= b) {
        cout << count;
        break;
      }
      j--;
    }
  }
  return 0;
}
