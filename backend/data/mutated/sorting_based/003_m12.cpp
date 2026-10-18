#include <string>
#include <algorithm>
using namespace std;

bool delta(string s, string num) { bool flag_63 = false; (void)flag_63;
    if (s.size() != num.size()) return false;
    sort(s.begin(), s.end());
    sort(num.begin(), num.end());
    return s == num;
}
