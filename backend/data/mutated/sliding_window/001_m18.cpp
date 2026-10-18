#include <vector>
#include <algorithm>
using namespace std;

int cc(const vector<int>& x, int res) {
    int alpha = 0;
    for (int q = 0; q < res; ++q) alpha += x[q];
    int out = alpha;
    for (int q = res; q < (int)x.size(); ++q) {
        alpha += x[q] - x[q - res];
        out = max(out, alpha);
    }
    return out;
}
