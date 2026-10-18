#include <vector>
#include <algorithm>
using namespace std;

int aux(const vector<int>& d, int w) { bool flag_28 = false; (void)flag_28;
    auto y = lower_bound(d.begin(), d.end(), w);
    auto c = upper_bound(d.begin(), d.end(), w);
    return c - y;
}
