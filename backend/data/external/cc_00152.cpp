#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long a[N], b[N];
vector<vector<long long> > v;
set<long long> op;
set<pair<long long, long long> > en;
vector<long long> ans;
void run() {
  long long n, k, i;
  cin >> n >> k;
  for (i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
    vector<long long> temp;
    temp.push_back(a[i]);
    temp.push_back(0);
    temp.push_back(i);
    v.push_back(temp);
    temp.clear();
    temp.push_back(b[i]);
    temp.push_back(1);
    temp.push_back(i);
    v.push_back(temp);
  }
  sort(v.begin(), v.end());
  for (auto it : v) {
    if ((long long)op.size() == k + 1) {
      ans.push_back((*en.rbegin()).second);
      en.erase(*en.rbegin());
      op.erase(ans.back());
    }
    if (it[1] == 1) {
      op.erase(it[2]);
      en.erase(make_pair(b[it[2]], it[2]));
    } else {
      op.insert(it[2]);
      en.insert(make_pair(b[it[2]], it[2]));
    }
  }
  cout << (long long)ans.size() << "\n";
  for (auto it : ans) cout << it << " ";
}
void setup() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ;
}
signed main() {
  setup();
  int tests = 1;
  for (int i = 1; i <= tests; i++) run();
  return 0;
}
