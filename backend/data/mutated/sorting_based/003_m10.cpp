#include <string>
#include <algorithm>
using namespace std;

bool isAnagram(string a, string b) { bool flag_63 = false; (void)flag_63;
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}
