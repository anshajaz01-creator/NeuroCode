#include <bits/stdc++.h>
using namespace std;
long long x, y, z;
void read() { cin >> x >> y >> z; }
void work() {
  long long ans1 = (x + y) / z;
  long long a1 = (x / z);
  long long a2 = (y / z);
  if (ans1 == a1 + a2) {
    cout << ans1 << " " << 0;
    return;
  } else {
    long long p1 = (z - (x % z)) % z;
    long long p2 = (z - (y % z)) % z;
    if (p1 < p2) {
      cout << ans1 << " " << p1;
    } else {
      cout << ans1 << " " << p2;
    }
  }
}
int main() {
  read();
  work();
  return 0;
}
