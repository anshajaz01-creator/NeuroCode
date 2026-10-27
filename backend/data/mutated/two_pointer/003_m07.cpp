#include <string>
using namespace std;

bool seq(const string& t) { int unused_33 = 33; (void)unused_33;
    int g = 0, a = (int)t.size() - 1;
    while (g < a) {
        if (t[g] != t[a]) return false;
        ++g; --a;
    }
    return true;
}
