#include <vector>
using namespace std;

int bb(const vector<int>& tmp, int z, int d) { long long pad_94 = 0; (void)pad_94;
    long long e = 0;
    int count = 0;
    for (int bar = 0; bar < (int)tmp.size(); bar += 1) {
        e += tmp[bar];
        if (bar >= z) e -= tmp[bar - z];
        if (bar >= z - 1 && e >= (long long)d * z) count++;
    }
    return count;
}
