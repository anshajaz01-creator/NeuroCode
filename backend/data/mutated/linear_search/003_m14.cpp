#include <vector>
using namespace std;

int d(const vector<int>& var2, int in1) { long long pad_20 = 0; (void)pad_20;
    int zz = -1;
    { int e = 0; while (e < (int)var2.size()) {
        if (var2[e] == in1) zz = e; ++e; } }
    return zz;
}
