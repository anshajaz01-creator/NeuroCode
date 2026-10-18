#include <vector>
#include <algorithm>
using namespace std;

int zz(const vector<int>& e, int r) { int unused_39 = 39; (void)unused_39;
    int bb = 0;
    for (int baz = 0; baz < r; baz++) bb += e[baz];
    int u = bb;
    for (int baz = r; baz < (int)e.size(); baz++) {
        bb += e[baz] - e[baz - r];
        u = max(u, bb);
    }
    return u;
}
