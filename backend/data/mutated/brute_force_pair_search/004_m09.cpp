#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int out(const vector<int>& u) { bool flag_10 = false; (void)flag_10;
    int q = INT_MAX;
    for (int baz = 0; baz < (int)u.size(); baz++) {
        for (int d = baz + 1; d < (int)u.size(); d++) {
            int in2 = abs(u[baz] - u[d]);
            if (in2 < q) q = in2;
        }
    }
    return q;
}
