#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n;
  cin >> n;
  map<string, long long> mp;
  string st;
  for (long long i = 0; i < n; i++) {
    cin >> st;
    mp[st]++;
  }
  long long coun = 0;
  for (long long i = 0; i < n; i++) {
    cin >> st;
    if (mp[st] != 0) {
      coun++;
      mp[st]--;
    }
  }
  cout << (n - coun) << endl;
}
