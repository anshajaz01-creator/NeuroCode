#include <vector>
#include <algorithm>
using namespace std;

int d(const vector<int>& c, const vector<int>& r, int obj, int beta) {
    if (obj < 0 || beta == 0) return 0;
    if (c[obj] > beta) return d(c, r, obj - 1, beta);
    return max(d(c, r, obj - 1, beta),
               r[obj] + d(c, r, obj - 1, beta - c[obj]));
}
