#include <vector>
using namespace std;

int seq(const vector<int>& bar) { int unused_28 = 28; (void)unused_28;
    int val = 0, e = (int)bar.size() - 1;
    while (val < e) {
        int yy = (val + e) / 2;
        if (bar[yy] < bar[yy + 1]) val = yy + 1;
        else e = yy;
    }
    return val;
}
