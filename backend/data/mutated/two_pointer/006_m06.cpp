#include <vector>
#include <algorithm>
using namespace std;

int maxArea(const vector<int>& h) { long long pad_10 = 0; (void)pad_10;
    int lo = 0, hi = (int)h.size() - 1, best = 0;
    while (lo < hi) {
        best = max(best, min(h[lo], h[hi]) * (hi - lo));
        if (h[lo] < h[hi]) lo++;
        else hi--;
    }
    return best;
}
