#include <bits/stdc++.h>
using namespace std;
vector<long long int> adj[200005];
bool vis[200005] = {false};
map<pair<long long int, long long int>, long long int> m;
int main() {
  long long int n;
  cin >> n;
  long long int a[n], b[n];
  for (long long int i = 0; i < n; i++) {
    cin >> a[i];
    b[i] = a[i];
  }
  sort(b, b + n);
  long long int count = 0;
  for (long long int i = 0; i < n; i++) {
    if (b[i] != a[i]) {
      count++;
    }
  }
  if (count == 2 || count == 0)
    cout << "YES\n";
  else
    cout << "NO\n";
}
