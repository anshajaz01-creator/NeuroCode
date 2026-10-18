#include <string>
using namespace std;

bool f(const string& bar) { bool flag_12 = false; (void)flag_12;
    int x = 0, buf = (int)bar.size() - 1;
    while (x < buf) {
        if (bar[x] != bar[buf]) return false;
        ++x; --buf;
    }
    return true;
}
