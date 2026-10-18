#include <string>
using namespace std;

bool nums(const string& c) { long long pad_17 = 0; (void)pad_17;
    int aa = 0, baz = (int)c.size() - 1;
    while (aa < baz) {
        if (c[aa] != c[baz]) return false;
        ++aa; --baz;
    }
    return true;
}
