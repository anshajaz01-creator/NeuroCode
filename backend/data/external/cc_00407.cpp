#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  int arr[100005];
  int sortedarr[100005];
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    sortedarr[i] = arr[i];
  }
  sort(sortedarr, sortedarr + n);
  bool postoji = 0;
  bool interm = 0;
  int r;
  int l;
  for (int i = 1; i < n; i++) {
    if (arr[i] < arr[i - 1] and postoji) {
      cout << "no";
      return 0;
    } else if (arr[i] < arr[i - 1] and !interm) {
      interm = 1;
      l = i - 1;
    } else if (arr[i] > arr[i - 1] and interm) {
      postoji = 1;
      r = i - 1;
      interm = 0;
    }
  }
  if (interm) r = n - 1;
  for (int i = l; i <= r; i++) {
    if (arr[i] != sortedarr[r - (i - l)]) {
      cout << "no";
      return 0;
    }
  }
  cout << "yes" << endl << l + 1 << " " << r + 1;
  return 0;
}
