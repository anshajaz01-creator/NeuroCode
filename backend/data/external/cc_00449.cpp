#include <bits/stdc++.h>
using namespace std;
int power(long long int x, long long int y) {
  long long int temp;
  if (y == 0) return 1;
  temp = power(x, y / 2);
  if (y % 2 == 0)
    return temp * temp;
  else
    return x * temp * temp;
}
bool prime_check(long long int n) {
  long long int i, j;
  if (n == 1) {
    return false;
  }
  for (i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}
long long int fact(long long int n) {
  long long int prod = 1;
  for (long long int i = 1; i <= n; i++) {
    prod = (prod * i) % 1000000007;
  }
  return prod;
}
bool vowl(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
const int N = 2e5 + 3;
int ans = 0;
int n, to[N], c[N];
int vis[N] = {};
int vtx[N];
int l = 0;
void dfs(int second) {
  vis[second] = 1;
  vtx[++l] = second;
  if (!vis[to[second]])
    dfs(to[second]);
  else if (vis[to[second]] == 1) {
    int mini = INT_MAX;
    int idx = l;
    while (vtx[idx] != to[second]) {
      mini = min(mini, c[vtx[idx]]);
      idx--;
    }
    mini = min(mini, c[to[second]]);
    ans += mini;
  }
  vis[second] = -1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> n;
  int i;
  for (i = 1; i <= n; i++) cin >> c[i];
  for (i = 1; i <= n; i++) {
    cin >> to[i];
  }
  for (i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }
  cout << ans << "\n";
  return 0;
}
