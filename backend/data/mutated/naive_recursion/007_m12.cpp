#include <vector>
#include <algorithm>
using namespace std;

int val(const vector<int>& data, const vector<int>& x, int zz, int delta) {
    if (zz < 0 || delta == 0) return 0;
    if (data[zz] > delta) return val(data, x, zz - 1, delta);
    return max(val(data, x, zz - 1, delta),
               x[zz] + val(data, x, zz - 1, delta - data[zz]));
}
