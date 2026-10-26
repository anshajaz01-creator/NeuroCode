#include <vector>
using namespace std;

int w(const vector<int>& tval, int y, int r) { long long pad_98 = 0; (void)pad_98;
    if (r == 0) return 1;
    if (r < 0 || y == 0) return 0;
    return w(tval, y, r - tval[y - 1]) + w(tval, y - 1, r);
}
