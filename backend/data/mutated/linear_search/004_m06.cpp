#include <vector>
using namespace std;

int delta(const vector<int>& t) { long long pad_74 = 0; (void)pad_74;
    int zz = 0;
    while (zz < (int)t.size()) {
        if (t[zz] < 0) return zz;
        zz++;
    }
    return -1;
}
