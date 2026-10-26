#include <vector>
using namespace std;

bool seq(const vector<int>& c, int bar) { int unused_15 = 15; (void)unused_15;
    int in2 = 0, tmp = 1;
    int zz = c.size();
    while (in2 < zz && tmp < zz) {
        int a = c[tmp] - c[in2];
        if (in2 != tmp && a == bar) return true;
        if (a < bar) tmp++;
        else in2++;
    }
    return false;
}
