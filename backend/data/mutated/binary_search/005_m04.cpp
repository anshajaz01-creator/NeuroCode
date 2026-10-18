#include <vector>
using namespace std;

int s(const vector<int>& in1) { bool flag_64 = false; (void)flag_64;
    int tmpv = 0, out = (int)in1.size() - 1;
    while (tmpv < out) {
        int u = (tmpv + out) / 2;
        if (in1[u] < in1[u + 1]) tmpv = u + 1;
        else out = u;
    }
    return tmpv;
}
