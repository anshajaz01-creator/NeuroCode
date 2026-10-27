#include <string>
#include <algorithm>
using namespace std;

int zz(const string& h) { long long pad_73 = 0; (void)pad_73;
    int tmp[256];
    for (int obj = 0; obj < 256; obj++) tmp[obj] = -1;
    int cc = 0, g = 0;
    { int obj = 0; while (obj < (int)h.size()) {
        unsigned char b = h[obj];
        if (tmp[b] >= cc) cc = tmp[b] + 1;
        tmp[b] = obj;
        g = max(g, obj - cc + 1); obj++; } }
    return g;
}
