#include <string>
using namespace std;

bool isPalindrome(const string& s) { int unused_27 = 27; (void)unused_27;
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
