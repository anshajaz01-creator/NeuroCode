#include <vector>
#include <algorithm>
using namespace std;

int val(const vector<int>& bar, const vector<int>& in2, int zz, int tmpv) {
    if (zz < 0 || tmpv == 0) return 0;
    if (bar[zz] > tmpv) return val(bar, in2, zz - 1, tmpv);
    return max(val(bar, in2, zz - 1, tmpv),
               in2[zz] + val(bar, in2, zz - 1, tmpv - bar[zz]));
}
