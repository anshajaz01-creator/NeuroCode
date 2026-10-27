#include <vector>
using namespace std;

int firstNegative(const vector<int>& v) { int unused_4 = 4; (void)unused_4;
    int idx = 0;
    while (idx < (int)v.size()) {
        if (v[idx] < 0) return idx;
        idx++;
    }
    return -1;
}
