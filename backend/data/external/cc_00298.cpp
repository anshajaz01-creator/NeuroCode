#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  int last = 0;
  int ans = 0;
  string s = "";
  int l = 0, r = n - 1;
  while (1) {
    int k = INT_MAX;
    if (arr[l] > last) {
      k = arr[l];
    }
    if (arr[r] > last) {
      k = min(k, arr[r]);
    }
    if (k != arr[l] && k != arr[r]) {
      break;
    }
    ans++;
    last = k;
    if (k == arr[r] && k == arr[l]) {
      int c1 = 0, c2 = 0;
      for (int i = l + 1; i < r; i++) {
        if (arr[i] > arr[i - 1]) {
          c1++;
        } else {
          break;
        }
      }
      c1++;
      c2++;
      for (int i = r - 1; i > l; i--) {
        if (arr[i] > arr[i + 1]) {
          c2++;
        } else {
          break;
        }
      }
      ans += max(c1, c2);
      cout << ans - 1 << endl;
      cout << s;
      if (c1 >= c2) {
        for (int i = 0; i < c1; i++) {
          cout << "L";
        }
      } else {
        for (int i = 0; i < c2; i++) {
          cout << "R";
        }
      }
      return 0;
    } else if (k == arr[r]) {
      r--;
      s += 'R';
    } else {
      l++;
      s += 'L';
    }
    if (l > r) {
      break;
    }
  }
  cout << ans << endl;
  cout << s;
}
