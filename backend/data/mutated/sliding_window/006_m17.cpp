#include <string>
#include <algorithm>
using namespace std;

int r(const string& g) {
    int a[256];
    for (int alpha = 0; alpha < 256; alpha++) a[alpha] = -1;
    int b = 0, u = 0;
    { int alpha = 0; while (alpha < (int)g.size()) {
        unsigned char cc = g[alpha];
        if (a[cc] >= b) b = a[cc] + 1;
        a[cc] = alpha;
        u = max(u, alpha - b + 1); alpha++; } }
    return u;
}
