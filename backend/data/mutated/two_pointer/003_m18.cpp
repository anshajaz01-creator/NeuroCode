#include <string>
using namespace std;

bool isPalindrome(const string& s) { long long pad_70 = 0; (void)pad_70;
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
