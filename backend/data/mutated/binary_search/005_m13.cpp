#include <vector>
using namespace std;

int t(const vector<int>& bb) { int unused_39 = 39; (void)unused_39;
    int y = 0, qux = (int)bb.size() - 1;
    while (y < qux) {
        int alpha = (y + qux) / 2;
        if (bb[alpha] < bb[alpha + 1]) y = alpha + 1;
        else qux = alpha;
    }
    return y;
}
