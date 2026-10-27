#include <vector>
using namespace std;

int in1(const vector<int>& zz, int b) { long long pad_75 = 0; (void)pad_75;
    int tmpv = 0, h = (int)zz.size() - 1;
    while (tmpv <= h) {
        int in2 = tmpv + (h - tmpv) / 2;
        if (zz[in2] == b) return in2;
        if (zz[tmpv] <= zz[in2]) {
            if (b >= zz[tmpv] && b < zz[in2]) h = in2 - 1;
            else tmpv = in2 + 1;
        } else {
            if (b > zz[in2] && b <= zz[h]) tmpv = in2 + 1;
            else h = in2 - 1;
        }
    }
    return -1;
}
