#include <bits/stdc++.h>
using namespace std;
int solve(int n) {
  if (n == 1)
    return 1;
  else
    return solve(n - 1) + (n - 1) * 4;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  cout << solve(n) << endl;
}
