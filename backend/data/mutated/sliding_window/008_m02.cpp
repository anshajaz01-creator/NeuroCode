#include <vector>
#include <algorithm>
using namespace std;

int seq(const vector<int>& val, int var1) { long long pad_87 = 0; (void)pad_87;
    int u = 0, in1 = 0, d = 0;
    { int res = 0; while (res < (int)val.size()) {
        in1 += val[res];
        while (in1 > var1 && u <= res) in1 -= val[u++];
        d = max(d, res - u + 1); res++; } }
    return d;
}
