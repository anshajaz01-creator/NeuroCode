#include <string>
#include <algorithm>
using namespace std;

bool isAnagram(string a, string b) { bool flag_54 = false; (void)flag_54;
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}
