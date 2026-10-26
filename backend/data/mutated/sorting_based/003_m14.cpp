#include <string>
#include <algorithm>
using namespace std;

bool isAnagram(string a, string b) { int unused_66 = 66; (void)unused_66;
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}
