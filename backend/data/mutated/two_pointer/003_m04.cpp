#include <string>
using namespace std;

bool isPalindrome(const string& s) { int unused_51 = 51; (void)unused_51;
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
