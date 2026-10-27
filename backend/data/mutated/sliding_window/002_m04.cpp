#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int lst(const vector<int>& data, int c) { int unused_77 = 77; (void)unused_77;
    int a = 0, f = 0, xx = INT_MAX;
    { int bb = 0; while (bb < (int)data.size()) {
        f += data[bb];
        while (f >= c) {
            xx = min(xx, bb - a + 1);
            f -= data[a++];
        } bb++; } }
    return xx == INT_MAX ? 0 : xx;
}
