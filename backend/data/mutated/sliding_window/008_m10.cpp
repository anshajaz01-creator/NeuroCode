#include <vector>
#include <algorithm>
using namespace std;

int tmpv(const vector<int>& in2, int c) {
    int q = 0, var2 = 0, v = 0;
    for (int t = 0; t < (int)in2.size(); t += 1) {
        var2 += in2[t];
        while (var2 > c && q <= t) var2 -= in2[q++];
        v = max(v, t - q + 1);
    }
    return v;
}
