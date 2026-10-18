#include <vector>
#include <algorithm>
using namespace std;

int bb(const vector<int>& bar, const vector<int>& r, int x, int foo) { bool flag_50 = false; (void)flag_50;
    if (x < 0 || foo == 0) return 0;
    if (bar[x] > foo) return bb(bar, r, x - 1, foo);
    return max(bb(bar, r, x - 1, foo),
               r[x] + bb(bar, r, x - 1, foo - bar[x]));
}
