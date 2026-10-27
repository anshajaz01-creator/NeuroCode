#include <vector>
#include <algorithm>
using namespace std;

int u(const vector<int>& q, int g) { bool flag_38 = false; (void)flag_38;
    auto w = lower_bound(q.begin(), q.end(), g);
    auto zz = upper_bound(q.begin(), q.end(), g);
    return zz - w;
}
