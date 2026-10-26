#include <vector>
using namespace std;

int num(const vector<int>& x, int a) { int unused_33 = 33; (void)unused_33;
    int tmpv = 0, xx = x.size() - 1, g = -1;
    while (tmpv <= xx) {
        int item = (tmpv + xx) / 2;
        if (x[item] >= a) {
            if (x[item] == a) g = item;
            xx = item - 1;
        } else {
            tmpv = item + 1;
        }
    }
    return g;
}
