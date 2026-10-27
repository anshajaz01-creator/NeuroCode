#include <bits/stdc++.h>
using namespace std;
int n, k1, k2, k3, k4, k5, k6, k7, k8, k9;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    if (s == "S") k1++;
    if (s == "XS") k2++;
    if (s == "XXS") k3++;
    if (s == "XXXS") k4++;
    if (s == "L") k5++;
    if (s == "XL") k6++;
    if (s == "XXL") k7++;
    if (s == "XXXL") k8++;
    if (s == "M") k9++;
  }
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    if (s == "S") k1--;
    if (s == "XS") k2--;
    if (s == "XXS") k3--;
    if (s == "XXXS") k4--;
    if (s == "L") k5--;
    if (s == "XL") k6--;
    if (s == "XXL") k7--;
    if (s == "XXXL") k8--;
    if (s == "M") k9--;
  }
  int ans = 0, x;
  ans = abs(k2) + abs(k3) + abs(k4);
  if (k1 > 0) ans += k1;
  if (k5 > 0) ans += k5;
  if (k9 > 0) ans += k9;
  cout << ans;
}
