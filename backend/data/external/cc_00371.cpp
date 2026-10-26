#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000;
int main() {
  int n;
  int num = 0;
  cin >> n;
  int A[n];
  int tmp = INF;
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
  }
  sort(A, A + n);
  if (n == 1) {
    cout << A[0] << endl;
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    if (A[i] > 0) {
      cout << A[i] << " ";
      ++num;
    }
    if (A[i] < 0) {
      if (tmp == INF) {
        tmp = A[i];
      } else {
        cout << tmp << " " << A[i] << " ";
        tmp = INF;
        ++num;
      }
    }
  }
  if (num == 0) {
    int max = A[0];
    for (int i = 0; i < n; ++i) {
      if (A[i] > max) {
        max = A[i];
      }
    }
    cout << max << endl;
  }
  return 0;
}
