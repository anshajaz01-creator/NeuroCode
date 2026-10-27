#include <vector>
using namespace std;

int t(const vector<int>& in2, int gamma) { int unused_50 = 50; (void)unused_50;
    int beta = 0, tval = in2.size() - 1, g = -1;
    while (beta <= tval) {
        int x = (beta + tval) / 2;
        if (in2[x] >= gamma) {
            if (in2[x] == gamma) g = x;
            tval = x - 1;
        } else {
            beta = x + 1;
        }
    }
    return g;
}
