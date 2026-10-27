#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
void solve() {
  long long int n;
  cin >> n;
  long long int a[n];
  long long int fre[200];
  memset(fre, 0, sizeof(fre));
  for (long long int i = 0; i < n; i++) {
    cin >> a[i];
    fre[a[i]]++;
  }
  long long int last = -1;
  for (long long int i = 0; i < 105; i++) {
    if (fre[i] == 0) {
      last = i;
      break;
    }
  }
  long long int last1 = -1;
  for (long long int i = 0; i < last; i++) {
    fre[i]--;
  }
  for (long long int i = 0; i < 105; i++) {
    if (fre[i] == 0) {
      last1 = i;
      break;
    }
  }
  cout << last1 + last << "\n";
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  srand(time(NULL));
  ;
  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    solve();
  }
}
