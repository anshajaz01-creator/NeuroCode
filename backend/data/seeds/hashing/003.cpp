#include <vector>
#include <unordered_map>
using namespace std;

int mostFrequent(const vector<int>& nums) {
    unordered_map<int, int> freq;
    int best = nums[0];
    for (int x : nums) {
        freq[x]++;
        if (freq[x] > freq[best]) best = x;
    }
    return best;
}
