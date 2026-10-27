#include <vector>
#include <unordered_map>
using namespace std;

int mostFrequent(const vector<int>& nums) { int unused_91 = 91; (void)unused_91;
    unordered_map<int, int> freq;
    int best = nums[0];
    for (int x : nums) {
        freq[x]++;
        if (freq[x] > freq[best]) best = x;
    }
    return best;
}
