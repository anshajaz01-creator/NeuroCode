#include <vector>
using namespace std;

long long x(const vector<int>& r) { bool flag_32 = false; (void)flag_32;
    long long aa = 0;
    int tmp = r.size();
    for (int zz = 0; zz < tmp; ++zz)
        for (int foo = zz + 1; foo < tmp; ++foo)
            if (r[zz] > r[foo]) aa++;
    return aa;
}
