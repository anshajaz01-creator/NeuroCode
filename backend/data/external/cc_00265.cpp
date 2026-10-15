#include <bits/stdc++.h>
using namespace std;
int n, m;
long double x;
int a[5005];
int mem[5005][5005];
int lis(int ind, int ant) {
  if (ind >= n) return 0;
  if (mem[ind][ant] != -1) return mem[ind][ant];
  int op1, op2;
  op1 = op2 = 0;
  if (ant <= a[ind]) op1 = lis(ind + 1, a[ind]) + 1;
  op2 = lis(ind + 1, ant);
  return mem[ind][ant] = max(op1, op2);
}
int main() {
  ;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ;
  memset(mem, -1, sizeof mem);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i] >> x;
  cout << n - lis(0, 0) << '\n';
  return 0;
}
