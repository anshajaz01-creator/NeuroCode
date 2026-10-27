#include <bits/stdc++.h>
using namespace std;
void O() {
  string a;
  cin >> a;
  char h = 'w';
  string r;
  cin >> r;
  if (a == "0" && r == "0") {
    cout << "OK" << endl;
    return;
  }
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != '0') {
      h = min(a[i], h);
    }
  }
  string s = "";
  s += h;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == h) {
      a.erase(a.begin() + i);
      break;
    }
  }
  sort((a).begin(), (a).end());
  s += a;
  if (s == r) {
    cout << "OK";
  } else {
    cout << "WRONG_ANSWER";
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  while (t--) O();
}
