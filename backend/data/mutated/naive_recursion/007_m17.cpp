#include <vector>
#include <algorithm>
using namespace std;

int var2(const vector<int>& var1, const vector<int>& delta, int t, int w) { long long pad_79 = 0; (void)pad_79;
    if (t < 0 || w == 0) return 0;
    if (var1[t] > w) return var2(var1, delta, t - 1, w);
    return max(var2(var1, delta, t - 1, w),
               delta[t] + var2(var1, delta, t - 1, w - var1[t]));
}
