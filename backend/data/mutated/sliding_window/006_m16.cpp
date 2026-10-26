#include <string>
#include <algorithm>
using namespace std;

int var2(const string& x) {
    int aa[256];
    for (int tval = 0; tval < 256; tval++) aa[tval] = -1;
    int y = 0, res = 0;
    { int tval = 0; while (tval < (int)x.size()) {
        unsigned char u = x[tval];
        if (aa[u] >= y) y = aa[u] + 1;
        aa[u] = tval;
        res = max(res, tval - y + 1); tval++; } }
    return res;
}
