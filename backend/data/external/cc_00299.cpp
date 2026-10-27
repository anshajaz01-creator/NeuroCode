#include <bits/stdc++.h>
using namespace std;
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t = 1;
  while (t--) {
    long long n;
    cin >> n;
    vector<long long> v(n);
    for (long long i = 0; i < n; i++) cin >> v[i];
    set<long long> left;
    set<long long> right;
    long long prev = -1;
    for (long long i = 0; i < n; i++) {
      if (v[i] > prev) {
        left.insert(v[i]);
        prev = v[i];
      } else
        break;
    }
    prev = -1;
    for (long long i = n - 1; i >= 0; i--) {
      if (v[i] > prev) {
        right.insert(v[i]);
        prev = v[i];
      } else
        break;
    }
    string res;
    while (left.size() != 0 or right.size() != 0) {
      if (left.size() != 0 and right.size() != 0) {
        long long l = *left.begin();
        long long r = *right.begin();
        if (l < r) {
          res.push_back('L');
          left.erase(l);
        } else if (r < l) {
          res.push_back('R');
          right.erase(r);
        } else if (l == r) {
          if (left.size() >= right.size()) {
            for (auto it : left) {
              res.push_back('L');
            }
            break;
          } else if (right.size() >= left.size()) {
            for (auto it : right) {
              res.push_back('R');
            }
            break;
          }
        }
      } else if (left.size() != 0 and right.size() == 0) {
        long long l = *left.begin();
        res.push_back('L');
        left.erase(l);
      } else if (right.size() != 0 and left.size() == 0) {
        long long r = *right.begin();
        res.push_back('R');
        right.erase(r);
      }
    }
    cout << res.length() << endl;
    cout << res << endl;
  }
}
