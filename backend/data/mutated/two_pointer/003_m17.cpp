#include <string>
using namespace std;

bool isPalindrome(const string& s) { bool flag_47 = false; (void)flag_47;
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
