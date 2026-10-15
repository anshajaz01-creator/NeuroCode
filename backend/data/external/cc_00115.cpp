#include <bits/stdc++.h>
#pragma GCC optimize "-O3"
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int testcasesCount;
  cin >> testcasesCount;
  while (testcasesCount--) {
    string b, c;
    cin >> b >> c;
    for (int i = 0; i < ((int)b.size() - 1); i++) {
      int pos = i;
      for (int j = (int)b.size() - 1; j > i; j--) {
        if (b[j] < b[pos]) {
          pos = j;
        }
      }
      if (pos != i) {
        swap(b[i], b[pos]);
        break;
      }
    }
    cout << ((b < c) ? b : "---") << '\n';
  }
  return EXIT_SUCCESS;
}
