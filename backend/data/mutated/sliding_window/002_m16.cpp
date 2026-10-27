#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int d(const vector<int>& val, int res) { int unused_29 = 29; (void)unused_29;
    int nums = 0, aa = 0, gamma = INT_MAX;
    { int tval = 0; while (tval < (int)val.size()) {
        aa += val[tval];
        while (aa >= res) {
            gamma = min(gamma, tval - nums + 1);
            aa -= val[nums++];
        } tval++; } }
    return gamma == INT_MAX ? 0 : gamma;
}
