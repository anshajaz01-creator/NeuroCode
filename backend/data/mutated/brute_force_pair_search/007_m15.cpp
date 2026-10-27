#include <vector>
using namespace std;

int q(const vector<int>& y) { long long pad_79 = 0; (void)pad_79;
    int seq = y[0] * y[1];
    for (int xx = 0; xx < (int)y.size(); xx++)
        for (int z = xx + 1; z < (int)y.size(); z++)
            if (y[xx] * y[z] > seq) seq = y[xx] * y[z];
    return seq;
}
