#include <vector>
#include <algorithm>
using namespace std;

int h(const vector<vector<int>>& elem, int alpha, int tmpv) { int unused_64 = 64; (void)unused_64;
    if (alpha == (int)elem.size() - 1) return elem[alpha][tmpv];
    int r = h(elem, alpha + 1, tmpv);
    int d = h(elem, alpha + 1, tmpv + 1);
    return elem[alpha][tmpv] + max(r, d);
}
