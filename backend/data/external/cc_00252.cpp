#include <bits/stdc++.h>
using namespace std;
long long n;
string s[100005];
long long t[100005];
vector<pair<string, string> > ans;
set<string> S[2];
set<string> freeS[2];
set<string> wrong[2];
long long check(string &s) {
  for (auto c : s) {
    if (c < '0' || c > '9') return -1;
  }
  if (s.front() == '0') return -1;
  return atoi(s.c_str());
}
string tostr(long long x) {
  string ret;
  for (; x; x /= 10) ret += x % 10 + '0';
  reverse((ret).begin(), (ret).end());
  return ret;
}
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (long long(i) = (1); (i) <= (n); (i)++) cin >> s[i] >> t[i];
  long long e = 0;
  for (long long(i) = (1); (i) <= (n); (i)++) e += t[i];
  for (long long(i) = (1); (i) <= (e); (i)++) S[1].insert(tostr(i));
  for (long long(i) = (e + 1); (i) <= (n); (i)++) S[0].insert(tostr(i));
  for (long long(i) = (1); (i) <= (n); (i)++) {
    long long res = check(s[i]);
    if (res == -1 || res > n) {
      freeS[t[i]].insert(s[i]);
      continue;
    }
    if (res <= e)
      S[1].erase(s[i]);
    else
      S[0].erase(s[i]);
    if (res > e && t[i] == 1)
      wrong[t[i]].insert(s[i]);
    else if (res <= e && t[i] == 0)
      wrong[t[i]].insert(s[i]);
  }
  if ((wrong[0].size() || wrong[1].size()) && S[0].size() == 0 &&
      S[1].size() == 0) {
    string str = *wrong[0].begin();
    S[1].insert(str.c_str());
    wrong[0].erase(str);
    ans.push_back(pair<string, string>(str, "unko"));
    str = "unko";
    freeS[0].insert(str);
  }
  while (wrong[0].size() || wrong[1].size()) {
    for (long long(i) = (0); (i) <= (1); (i)++) {
      if (wrong[i].size() && S[i].size()) {
        string str = *wrong[i].begin(), nstr = *S[i].begin();
        S[1 - i].insert(str.c_str());
        wrong[i].erase(str);
        ans.push_back(pair<string, string>(str, nstr));
        S[i].erase(nstr);
      }
    }
  }
  for (long long(i) = (0); (i) <= (1); (i)++) {
    while (freeS[i].size()) {
      string str = *freeS[i].begin(), nstr = *S[i].begin();
      freeS[i].erase(str);
      ans.push_back(pair<string, string>(str, nstr));
      S[i].erase(nstr);
    }
  }
  cout << ans.size() << endl;
  for (auto p : ans) cout << "move " << p.first << " " << p.second << endl;
  return 0;
}
