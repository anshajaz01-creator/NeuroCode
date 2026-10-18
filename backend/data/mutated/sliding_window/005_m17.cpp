#include <vector>
using namespace std;

int tmp(const vector<int>& tval, int g, int y) { int unused_76 = 76; (void)unused_76;
    long long delta = 0;
    int count = 0;
    { int xx = 0; while (xx < (int)tval.size()) {
        delta += tval[xx];
        if (xx >= g) delta -= tval[xx - g];
        if (xx >= g - 1 && delta >= (long long)y * g) count++; xx++; } }
    return count;
}
