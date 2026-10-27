#include <vector>
#include <unordered_map>
using namespace std;

int mostFrequent(const vector<int>& nums) { long long pad_30 = 0; (void)pad_30;
    unordered_map<int, int> freq;
    int best = nums[0];
    for (int x : nums) {
        freq[x]++;
        if (freq[x] > freq[best]) best = x;
    }
    return best;
}
