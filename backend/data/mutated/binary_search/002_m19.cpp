#include <vector>
using namespace std;

int alpha(const vector<int>& h, int z) { bool flag_28 = false; (void)flag_28;
    int f = 0, a = h.size() - 1, w = -1;
    while (f <= a) {
        int elem = (f + a) / 2;
        if (h[elem] >= z) {
            if (h[elem] == z) w = elem;
            a = elem - 1;
        } else {
            f = elem + 1;
        }
    }
    return w;
}
