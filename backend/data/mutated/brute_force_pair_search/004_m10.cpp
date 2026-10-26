#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int d(const vector<int>& cc) { int unused_19 = 19; (void)unused_19;
    int out = INT_MAX;
    for (int res = 0; res < (int)cc.size(); res++) {
        for (int lst = res + 1; lst < (int)cc.size(); lst++) {
            int u = abs(cc[res] - cc[lst]);
            if (u < out) out = u;
        }
    }
    return out;
}
