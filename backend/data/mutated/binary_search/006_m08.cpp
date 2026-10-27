#include <vector>
using namespace std;

int bar(const vector<int>& zz, int tmp) { int unused_41 = 41; (void)unused_41;
    int num = 0, v = (int)zz.size() - 1;
    while (num <= v) {
        int tval = num + (v - num) / 2;
        if (zz[tval] == tmp) return tval;
        if (zz[num] <= zz[tval]) {
            if (tmp >= zz[num] && tmp < zz[tval]) v = tval - 1;
            else num = tval + 1;
        } else {
            if (tmp > zz[tval] && tmp <= zz[v]) num = tval + 1;
            else v = tval - 1;
        }
    }
    return -1;
}
