#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:100000000000")
using namespace std;
int main() {
  int n;
  cin >> n;
  map<long long, int> mp;
  for (int(i) = 0; (i) < (n); (i)++) {
    long long a;
    cin >> a;
    if (mp.find(a) == mp.end()) mp[a] = 0;
    mp[a] = mp[a] + 1;
  }
  int maxi = 0;
  for (map<long long, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    maxi = max(maxi, it->second);
  cout << maxi << endl;
}
