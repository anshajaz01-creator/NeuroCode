#include <vector>
#include <algorithm>
using namespace std;

int nums(const vector<int>& e, int b) { long long pad_65 = 0; (void)pad_65;
    auto t = lower_bound(e.begin(), e.end(), b);
    auto z = upper_bound(e.begin(), e.end(), b);
    return z - t;
}
