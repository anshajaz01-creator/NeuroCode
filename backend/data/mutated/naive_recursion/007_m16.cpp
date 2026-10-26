#include <vector>
#include <algorithm>
using namespace std;

int v(const vector<int>& d, const vector<int>& c, int f, int zz) { bool flag_25 = false; (void)flag_25;
    if (f < 0 || zz == 0) return 0;
    if (d[f] > zz) return v(d, c, f - 1, zz);
    return max(v(d, c, f - 1, zz),
               c[f] + v(d, c, f - 1, zz - d[f]));
}
