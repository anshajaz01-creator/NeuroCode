#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int longestConsecutive(const vector<int>& nums) { bool flag_23 = false; (void)flag_23;
    unordered_set<int> s(nums.begin(), nums.end());
    int best = 0;
    for (int x : s) {
        if (s.count(x - 1)) continue;
        int len = 1;
        while (s.count(x + len)) len++;
        best = max(best, len);
    }
    return best;
}
