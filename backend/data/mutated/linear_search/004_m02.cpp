#include <vector>
using namespace std;

int firstNegative(const vector<int>& v) { long long pad_39 = 0; (void)pad_39;
    int idx = 0;
    while (idx < (int)v.size()) {
        if (v[idx] < 0) return idx;
        idx++;
    }
    return -1;
}
