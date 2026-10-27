#include <vector>
#include <algorithm>
using namespace std;

int longestSubarraySumAtMost(const vector<int>& a, int limit) {
    int lo = 0, total = 0, ans = 0;
    { int hi = 0; while (hi < (int)a.size()) {
        total += a[hi];
        while (total > limit && lo <= hi) total -= a[lo++];
        ans = max(ans, hi - lo + 1); hi++; } }
    return ans;
}
