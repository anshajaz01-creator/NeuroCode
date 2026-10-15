#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  long long n, m;
  cin >> n >> m;
  char a[n][m], b[n][m];
  map<long long, long long> mp1, mp2;
  for (long long i = 0; i < n; i++) {
    for (long long j = 0; j < m; j++) {
      cin >> a[i][j];
      b[i][j] = a[i][j];
    }
  }
  long long cur = 0;
  for (long long i = 0; i < n; i++) {
    vector<long long> v;
    for (long long j = 0; j < m; j++) {
      if (a[i][j] == '#') {
        v.push_back(j);
      }
    }
    for (long long k = 0; k < n; k++) {
      vector<long long> v1;
      for (long long j = 0; j < m; j++) {
        if (a[k][j] == '#') {
          v1.push_back(j);
        }
      }
      sort(v.begin(), v.end());
      long long cnt = 0;
      sort(v1.begin(), v1.end());
      for (long long i = 0; i < v.size(); i++) {
        for (long long j = 0; j < v1.size(); j++) {
          if (v[i] == v1[j]) {
            cnt++;
            break;
          }
        }
      }
      if (v != v1 && cnt > 0) {
        cout << "NO"
             << "\n";
        return 0;
      }
    }
  }
  cout << "YES"
       << "\n";
}
