#include <bits/stdc++.h>
using namespace std;
int main() {
  int i, j, k, l = 0, m, n;
  int arr[500], arr1[500], arr2[500] = {0}, arr3[500];
  cin >> n >> m >> k;
  for (i = 0; i < n; i++) cin >> arr[i];
  for (i = 0; i < n; i++) {
    cin >> arr1[i];
    if (arr2[arr1[i] - 1] < arr[i]) {
      arr2[arr1[i] - 1] = arr[i];
      arr3[arr1[i] - 1] = i + 1;
    }
  }
  int a;
  for (i = 0; i < k; i++) {
    cin >> a;
    if (arr3[arr1[a - 1] - 1] != a) l++;
  }
  cout << l;
}
