#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int main() {
  int n;
  while (cin >> n) {
    string s;
    vector<string> v1;
    vector<string> v2;
    vector<string>::iterator it;
    for (int i = 0; i < n; i++) {
      cin >> s;
      v1.push_back(s);
    }
    for (int i = 0; i < n; i++) {
      cin >> s;
      v2.push_back(s);
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (v1[i] == v2[j]) {
          v2[j] = '0';
          break;
        }
        if (j == n - 1) sum++;
      }
    }
    cout << sum << endl;
  }
  return 0;
}
