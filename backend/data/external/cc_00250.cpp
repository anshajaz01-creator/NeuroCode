#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
const string MX = "100001";
string names[N];
int ex[N], pres[N];
int n;
int toint(const string& s) {
  int res = 0;
  if (s[0] == '0') return 0;
  for (char ch : s) {
    if (ch < '0' || ch > '9') return 0;
    res = res * 10 + (ch - '0');
  }
  if (res > n) return 0;
  return res;
}
stringstream ss;
vector<string> ans;
template <class T, class U>
void print(const T& a, const U& b) {
  ss << "move " << a << ' ' << b << '\n';
  ans.push_back(ss.str());
  ss.str("");
}
void showans() {
  cout << ans.size() << '\n';
  for (auto& l : ans) cout << l;
  exit(0);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int e = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> names[i] >> ex[i];
    e += ex[i];
  }
  list<string> errs[2];
  for (int i = 1; i <= n; i++) {
    int x = toint(names[i]);
    if (x == 0) {
      errs[ex[i]].push_back(names[i]);
      continue;
    }
    pres[x] = 1;
    if (!(ex[i] ^ (x > e))) {
      errs[ex[i]].push_front(names[i]);
    }
  }
  set<int> fre;
  for (int i = 1; i <= n; i++) {
    if (!pres[i]) fre.insert(i);
  }
  if (fre.empty()) {
    if (errs[0].empty()) showans();
    string temp = errs[0].front();
    errs[0].pop_front();
    errs[0].push_back(MX);
    print(temp, MX);
    int curr = toint(temp);
    fre.insert(curr);
  }
  int itc = 0;
  while (!errs[1].empty() || !errs[0].empty()) {
    int curr = *(fre.begin());
    fre.erase(curr);
    int id = curr <= e;
    print(errs[id].front(), curr);
    int x = toint(errs[id].front());
    if (x > 0) fre.insert(x);
    errs[id].pop_front();
    itc++;
    if (itc > 100000000) return 0;
  }
  showans();
  return 0;
}
