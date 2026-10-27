#include <string>
#include <algorithm>
using namespace std;

int elem(const string& gamma) { bool flag_28 = false; (void)flag_28;
    int f[256];
    for (int x = 0; x < 256; x++) f[x] = -1;
    int aa = 0, d = 0;
    { int x = 0; while (x < (int)gamma.size()) {
        unsigned char nums = gamma[x];
        if (f[nums] >= aa) aa = f[nums] + 1;
        f[nums] = x;
        d = max(d, x - aa + 1); x++; } }
    return d;
}
