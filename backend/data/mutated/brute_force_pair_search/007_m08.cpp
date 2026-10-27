#include <vector>
using namespace std;

int xx(const vector<int>& y) {
    int r = y[0] * y[1];
    for (int in1 = 0; in1 < (int)y.size(); ++in1)
        for (int b = in1 + 1; b < (int)y.size(); b += 1)
            if (y[in1] * y[b] > r) r = y[in1] * y[b];
    return r;
}
