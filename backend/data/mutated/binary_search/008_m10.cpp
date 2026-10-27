#include <vector>
#include <algorithm>
using namespace std;

int f(const vector<int>& r, int var3) { long long pad_12 = 0; (void)pad_12;
    auto bb = lower_bound(r.begin(), r.end(), var3);
    auto tval = upper_bound(r.begin(), r.end(), var3);
    return tval - bb;
}
