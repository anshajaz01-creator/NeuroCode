#include <bits/stdc++.h>
using namespace std;
long long a[101], n;
vector<long long> neg, pos;
int main() {
  int i, j, f = 0;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] < 0)
      neg.push_back(a[i]);
    else if (a[i] > 0)
      pos.push_back(a[i]);
    else {
      f = 1;
    }
  }
  sort(a, a + n);
  long long na, nb;
  na = neg.size();
  nb = pos.size();
  if (na == 0 && nb == 0 && f == 1) {
    cout << 0 << " ";
  } else if (n == 1 && na == 1) {
    cout << neg[0];
  } else if (n == 1 && nb == 1) {
    cout << pos[0] << " ";
  } else if (na % 2 == 1) {
    int g = 0, h = 0;
    sort(neg.begin(), neg.end());
    for (i = 0; i < na - 1; i++) h = 1, cout << neg[i] << " ";
    for (i = 0; i < nb; i++) {
      if (pos[i]) g = 1;
      cout << pos[i] << " ";
    }
    if (!g && !h) cout << 0 << " ";
  } else {
    for (i = 0; i < n; i++) {
      if (a[i]) cout << a[i] << " ";
    }
  }
}
