#include <vector>
#include <algorithm>
using namespace std;

int qux(const vector<int>& s) { bool flag_60 = false; (void)flag_60;
    int alpha = 0, v = (int)s.size() - 1, foo = 0;
    while (alpha < v) {
        foo = max(foo, min(s[alpha], s[v]) * (v - alpha));
        if (s[alpha] < s[v]) alpha++;
        else v--;
    }
    return foo;
}
