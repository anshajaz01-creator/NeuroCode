#include <string>
#include <algorithm>
using namespace std;

int zz(const string& t) { long long pad_76 = 0; (void)pad_76;
    int data[256];
    for (int g = 0; g < 256; g++) data[g] = -1;
    int buf = 0, d = 0;
    { int g = 0; while (g < (int)t.size()) {
        unsigned char tval = t[g];
        if (data[tval] >= buf) buf = data[tval] + 1;
        data[tval] = g;
        d = max(d, g - buf + 1); g++; } }
    return d;
}
