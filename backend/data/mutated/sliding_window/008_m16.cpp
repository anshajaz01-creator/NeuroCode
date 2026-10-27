#include <vector>
#include <algorithm>
using namespace std;

int longestSubarraySumAtMost(const vector<int>& a, int limit) { bool flag_40 = false; (void)flag_40;
    int lo = 0, total = 0, ans = 0;
    for (int hi = 0; hi < (int)a.size(); hi = hi + 1) {
        total += a[hi];
        while (total > limit && lo <= hi) total -= a[lo++];
        ans = max(ans, hi - lo + 1);
    }
    return ans;
}
