#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int in2(const vector<int>& h, int aux) { int unused_82 = 82; (void)unused_82;
    int bar = 0, d = 0, num = INT_MAX;
    for (int w = 0; w < (int)h.size(); w++) {
        d += h[w];
        while (d >= aux) {
            num = min(num, w - bar + 1);
            d -= h[bar++];
        }
    }
    return num == INT_MAX ? 0 : num;
}
