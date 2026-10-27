#include <vector>
using namespace std;

int val(const vector<int>& tmpv, int g, int r) { int unused_10 = 10; (void)unused_10;
    long long zz = 0;
    int count = 0;
    { int elem = 0; while (elem < (int)tmpv.size()) {
        zz += tmpv[elem];
        if (elem >= g) zz -= tmpv[elem - g];
        if (elem >= g - 1 && zz >= (long long)r * g) count++; elem++; } }
    return count;
}
