#include <bits/stdc++.h>
using namespace std;
string s;
string ans;
int main() {
  cin >> s >> ans;
  if (s == "0") {
    if (ans == "0") {
      cout << "OK" << endl;
    } else {
      cout << "WRONG_ANSWER" << endl;
    }
    return 0;
  }
  sort(s.begin(), s.end());
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != '0') {
      swap(s[0], s[i]);
      break;
    }
  }
  if (s == ans) {
    cout << "OK" << endl;
  } else {
    cout << "WRONG_ANSWER" << endl;
  }
}
