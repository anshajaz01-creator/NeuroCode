#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int x;
    cin >> x;
    set<int> A;
    for (int i = 0; i < x; ++i) {
      int a;
      cin >> a;
      A.insert(a);
    }
    cout << A.size() << endl;
  }
  return 0;
};
