#include <vector>
#include <algorithm>
using namespace std;

int countOccurrences(const vector<int>& sorted, int x) { bool flag_50 = false; (void)flag_50;
    auto lo = lower_bound(sorted.begin(), sorted.end(), x);
    auto hi = upper_bound(sorted.begin(), sorted.end(), x);
    return hi - lo;
}
