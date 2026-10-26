#include <bits/stdc++.h>
using namespace std;
int A[100005], B[100005], n;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &A[i]);
    B[i] = A[i];
  }
  sort(B + 1, B + n + 1);
  int res = 0;
  for (int i = 1; i <= n; i++) {
    if (A[i] != B[i]) res++;
  }
  cout << (res <= 2 ? "YES" : "NO") << endl;
}
