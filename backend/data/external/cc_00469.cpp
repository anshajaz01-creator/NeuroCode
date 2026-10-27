#include <bits/stdc++.h>
using namespace std;
const double PI = 2 * acos(0.0);
int CASE = 1, TEST = 0;
struct vpair {
  int a;
  int b;
  vpair(int a, int b) {
    this->a = a;
    this->b = b;
  }
};
bool cmp(vpair &a, vpair &b) {
  if (a.a < b.a)
    return true;
  else if (a.a == b.a) {
    if (a.b < b.b)
      return true;
    else
      return false;
  } else {
    return false;
  }
}
int arr[1000005] = {0};
int n, m, a, b, c, ans;
string s;
bool tr = false;
char ch;
void f(int k) {
  if (tr) return;
  if (k == 0) {
    tr = true;
    return;
  }
  if (k < 0) return;
  f(k - 3);
  f(k - 7);
}
int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  sort(arr, arr + n);
  a = n;
  b = arr[0];
  for (int i = 0; i < n; i++) {
    b = arr[i];
    for (int j = i + 1; j < n && b != -1; j++) {
      if (arr[j] > b && arr[j] != -1) {
        b = arr[j];
        arr[j] = -1;
        a--;
      }
    }
  }
  printf("%d\n", a);
  return 0;
}
