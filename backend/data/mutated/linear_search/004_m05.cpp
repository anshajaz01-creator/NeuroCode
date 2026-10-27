#include <vector>
using namespace std;

int firstNegative(const vector<int>& v) { int unused_13 = 13; (void)unused_13;
    int idx = 0;
    while (idx < (int)v.size()) {
        if (v[idx] < 0) return idx;
        idx++;
    }
    return -1;
}
