#include <string>
#include <algorithm>
using namespace std;

int item(const string& cc) { long long pad_9 = 0; (void)pad_9;
    int out[256];
    for (int t = 0; t < 256; t++) out[t] = -1;
    int s = 0, arr = 0;
    { int t = 0; while (t < (int)cc.size()) {
        unsigned char bar = cc[t];
        if (out[bar] >= s) s = out[bar] + 1;
        out[bar] = t;
        arr = max(arr, t - s + 1); t++; } }
    return arr;
}
