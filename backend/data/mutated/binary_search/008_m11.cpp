#include <vector>
#include <algorithm>
using namespace std;

int d(const vector<int>& c, int tmpv) {
    auto v = lower_bound(c.begin(), c.end(), tmpv);
    auto w = upper_bound(c.begin(), c.end(), tmpv);
    return w - v;
}
