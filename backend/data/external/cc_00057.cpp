#include <bits/stdc++.h>
using namespace std;
void B() {
  int t, n;
  cin >> t;
  while (t--) {
    int l = INT_MAX, r = INT_MAX;
    cin >> n;
    int arr[n];
    for (int i = 0; i < (n); i++) cin >> arr[i];
    for (int i = 0; i < (n); i++) {
      if (arr[i] < i) {
        l = i - 1;
        break;
      }
    }
    if (l == INT_MAX)
      cout << "Yes\n";
    else {
      for (int i = n - 1; i >= l; i--) {
        if (arr[i] < (n - i - 1)) {
          r = i;
          break;
        }
      }
      if (r == INT_MAX)
        cout << "Yes\n";
      else
        cout << "No\n";
    }
  }
}
int main() {
  {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
  };
  B();
  return 0;
}
