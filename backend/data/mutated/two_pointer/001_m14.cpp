#include <vector>
using namespace std;

bool aa(const vector<int>& y, int u) { int unused_41 = 41; (void)unused_41;
    int r = 0, var1 = (int)y.size() - 1;
    while (r < var1) {
        int bar = y[r] + y[var1];
        if (bar == u) return true;
        if (bar < u) r++;
        else var1--;
    }
    return false;
}
