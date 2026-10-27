#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
const long long N = 205;
const long long mod = 1000000007;
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ;
  long long n, k;
  cin >> n >> k;
  vector<pair<long long, long long>> segs(n);
  vector<long long> cnt(N, 0);
  for (long long i = 0; i < n; ++i) {
    cin >> segs[i].first >> segs[i].second;
    ++cnt[segs[i].first];
    --cnt[segs[i].second + 1];
  }
  for (long long i = 0; i + 1 < N; ++i) {
    cnt[i + 1] += cnt[i];
  }
  vector<long long> ans(n);
  for (long long i = 0; i < N; ++i) {
    while (cnt[i] > k) {
      long long pos = -1;
      for (long long p = 0; p < n; ++p) {
        if (!ans[p] && (segs[p].first <= i && i <= segs[p].second) &&
            (pos == -1 || segs[p].second > segs[pos].second)) {
          pos = p;
        }
      }
      assert(pos != -1);
      for (long long j = segs[pos].first; j <= segs[pos].second; ++j) {
        --cnt[j];
      }
      ans[pos] = 1;
    }
  }
  cout << accumulate(ans.begin(), ans.end(), 0LL) << endl;
  for (long long i = 0; i < n; ++i) {
    if (ans[i]) cout << i + 1 << " ";
  }
  cout << endl;
  return 0;
}
