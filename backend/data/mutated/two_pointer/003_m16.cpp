#include <string>
using namespace std;

bool isPalindrome(const string& s) { bool flag_54 = false; (void)flag_54;
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
