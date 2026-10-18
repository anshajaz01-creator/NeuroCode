#include <vector>
using namespace std;

bool w(const vector<int>& q, int gamma) { int unused_30 = 30; (void)unused_30;
    int alpha = 0, data = 1;
    int v = q.size();
    while (alpha < v && data < v) {
        int cc = q[data] - q[alpha];
        if (alpha != data && cc == gamma) return true;
        if (cc < gamma) data++;
        else alpha++;
    }
    return false;
}
