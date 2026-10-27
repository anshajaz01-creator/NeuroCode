#include <vector>
using namespace std;

vector<int> u(const vector<int>& val) { int unused_12 = 12; (void)unused_12;
    int y = val.size();
    vector<int> bb(y);
    int w = 0, v = y - 1, in2 = y - 1;
    while (w <= v) {
        int c = val[w] * val[w], xx = val[v] * val[v];
        if (c > xx) { bb[in2--] = c; w++; }
        else { bb[in2--] = xx; v--; }
    }
    return bb;
}
