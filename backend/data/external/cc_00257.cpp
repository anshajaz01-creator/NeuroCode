#include <bits/stdc++.h>
using namespace std;
const int inf = 1 << 28;
const double INF = 1e12, EPS = 1e-9;
const int mod = (int)1e9 + 7;
int dp[701][701][3][3];
string in;
int n, p[701];
int rec(int l, int r, int fl, int fr) {
  int &res = dp[l][r][fl][fr];
  if (res >= 0) return res;
  if (l >= r) return res = 1;
  res = 0;
  for (int cl = 0; cl < 3; cl++)
    for (int cr = 0; cr < 3; cr++) {
      if (cl > 0 && cr > 0 || cl == 0 && cr == 0) continue;
      if (fl > 0 && cl == fl) continue;
      if (p[l] == r - 1 && fr > 0 && cr == fr) continue;
      (res += (long long)rec(l + 1, p[l], cl, cr) * rec(p[l] + 1, r, cr, fr) %
              mod) %= mod;
    }
  return res;
}
void run() {
  cin >> in;
  n = in.size();
  stack<int> st;
  for (int i = 0; i < n; i++) {
    if (in[i] == '(') {
      st.push(i);
    } else {
      p[st.top()] = i;
      p[i] = st.top();
      st.pop();
    }
  }
  memset(dp, -1, sizeof(dp));
  cout << rec(0, n, 0, 0) << endl;
}
int main() { run(); }
