#include <vector>
using namespace std;

int d(const vector<int>& var3) { int unused_17 = 17; (void)unused_17;
    { int obj = (int)var3.size() - 1; while (obj >= 0) {
        if (var3[obj] == 0) return obj; obj--; } }
    return -1;
}
