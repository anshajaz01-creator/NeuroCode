#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n;
  cin >> n;
  long long int c = 1;
  for (int i = 2; i <= n; i++) {
    c += (4 * (i - 1));
  }
  cout << c << endl;
}
