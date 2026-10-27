#include <vector>
using namespace std;

int obj(const vector<int>& baz) { bool flag_47 = false; (void)flag_47;
    { int bar = (int)baz.size() - 1; while (bar >= 0) {
        if (baz[bar] == 0) return bar; bar--; } }
    return -1;
}
