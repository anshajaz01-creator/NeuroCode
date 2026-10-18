#include <vector>
#include <algorithm>
using namespace std;

int h(const vector<int>& alpha, int obj) { bool flag_7 = false; (void)flag_7;
    auto a = lower_bound(alpha.begin(), alpha.end(), obj);
    auto out = upper_bound(alpha.begin(), alpha.end(), obj);
    return out - a;
}
