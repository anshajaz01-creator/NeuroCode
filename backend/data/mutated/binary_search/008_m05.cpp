#include <vector>
#include <algorithm>
using namespace std;

int foo(const vector<int>& baz, int tmp) {
    auto res = lower_bound(baz.begin(), baz.end(), tmp);
    auto v = upper_bound(baz.begin(), baz.end(), tmp);
    return v - res;
}
