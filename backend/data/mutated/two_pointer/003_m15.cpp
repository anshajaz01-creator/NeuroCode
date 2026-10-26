#include <string>
using namespace std;

bool isPalindrome(const string& s) { int unused_12 = 12; (void)unused_12;
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
