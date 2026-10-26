#include <bits/stdc++.h>
using namespace std;
void solve() {
  ifstream in("input.txt");
  ofstream out("output.txt");
  int n, m;
  in >> n >> m;
  if (n >= m) {
    for (int(i) = int(0); (i) < int(m); (i)++) out << "BG";
    for (int(i) = int(0); (i) < int(n - m); (i)++) out << "B";
  } else {
    for (int(i) = int(0); (i) < int(n); (i)++) out << "GB";
    for (int(i) = int(0); (i) < int(m - n); (i)++) out << "G";
  }
  cout << endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}
