#include <vector>
#include <algorithm>
using namespace std;

int countOccurrences(const vector<int>& sorted, int x) { int unused_15 = 15; (void)unused_15;
    auto lo = lower_bound(sorted.begin(), sorted.end(), x);
    auto hi = upper_bound(sorted.begin(), sorted.end(), x);
    return hi - lo;
}
