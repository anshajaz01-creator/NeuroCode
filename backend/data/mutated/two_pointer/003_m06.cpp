#include <string>
using namespace std;

bool c(const string& xx) { bool flag_47 = false; (void)flag_47;
    int r = 0, delta = (int)xx.size() - 1;
    while (r < delta) {
        if (xx[r] != xx[delta]) return false;
        ++r; --delta;
    }
    return true;
}
