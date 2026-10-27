#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  int a[n][2];
  for (int i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1];
  }
  char choice[n];
  int diff;
  if (a[0][0] < 500) {
    choice[0] = 'A';
    diff = a[0][0];
  } else {
    choice[0] = 'G';
    diff = -a[0][1];
  }
  for (int i = 1; i < n; i++) {
    if (diff + a[i][0] < 500) {
      choice[i] = 'A';
      diff += a[i][0];
    } else {
      choice[i] = 'G';
      diff -= a[i][1];
    }
  }
  for (int i = 0; i < n; i++) {
    cout << choice[i];
  }
  return 0;
}
