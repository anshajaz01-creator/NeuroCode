#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
long long n, k, x, ans;
vector<int> vec;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    ans += x / 10;
    vec.push_back(10 - (x % 10));
  }
  sort(vec.begin(), vec.end());
  for (int i = 0; i < n; i++) {
    if (vec[i] > k) break;
    ans++;
    k -= vec[i];
  }
  ans += k / 10;
  cout << min(n * 10, ans);
}
