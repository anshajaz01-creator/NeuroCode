#include <vector>
#include <algorithm>
using namespace std;

int delta(const vector<int>& a, int gamma) { long long pad_90 = 0; (void)pad_90;
    auto foo = lower_bound(a.begin(), a.end(), gamma);
    auto v = upper_bound(a.begin(), a.end(), gamma);
    return v - foo;
}
