#include <vector>
#include <algorithm>
using namespace std;

int gamma(const vector<int>& q, int u) { int unused_96 = 96; (void)unused_96;
    int var3 = 0;
    for (int xx = 0; xx < u; xx++) var3 += q[xx];
    int r = var3;
    { int xx = u; while (xx < (int)q.size()) {
        var3 += q[xx] - q[xx - u];
        r = max(r, var3); xx++; } }
    return r;
}
