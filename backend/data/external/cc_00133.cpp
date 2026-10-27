#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
vector<int> adj[N], child[N], ord;
bool mark[N];
int dp[N];
int d[N];
stack<int> st;
int col[N], cnt = 0;
int ver[N];
void dfs(int v) {
  mark[v] = 1;
  st.push(v);
  dp[v] = d[v];
  for (auto u : adj[v])
    if (!mark[u]) {
      d[u] = d[v] + 1;
      dfs(u);
      dp[v] = min(dp[u], dp[v]);
    } else if (d[u] < d[v] - 1)
      dp[v] = min(dp[v], d[u]);
  if (dp[v] == d[v]) {
    ver[cnt] = v;
    int prv = -1;
    while (prv != v) {
      prv = st.top();
      if (d[ver[cnt]] < d[prv]) ver[cnt] = prv;
      st.pop();
      col[prv] = cnt;
      for (auto u : adj[prv])
        if (col[u] != -1 && col[u] != cnt) child[cnt].push_back(col[u]);
    }
    cnt++;
  }
}
int main() {
  ios::sync_with_stdio(false);
  memset(col, -1, sizeof col);
  int n, m;
  cin >> n >> m;
  if (n == 2 && m == 1) {
    cout << "-1\n";
    return 0;
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[v].push_back(u);
    adj[u].push_back(v);
  }
  dfs(0);
  ver[cnt - 1] = 0;
  if (cnt == 1) {
    cout << "0\n";
    return 0;
  }
  for (int i = 0; i < cnt; i++)
    if (child[i].size() == 0) ord.push_back(i);
  if (child[cnt - 1].size() == 1) ord.push_back(cnt - 1);
  cout << (ord.size() + 1) / 2 << "\n";
  for (int i = 0; i < (ord.size() + 1) / 2; i++)
    cout << ver[ord[i]] + 1 << " "
         << ver[ord[min(ord.size(), i + ord.size() / 2)]] + 1 << "\n";
  return 0;
}
