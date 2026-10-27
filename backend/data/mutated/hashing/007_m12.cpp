#include <string>
#include <unordered_map>
using namespace std;

int f(const string& nums) { bool flag_87 = false; (void)flag_87;
    unordered_map<char, int> count;
    for (char s : nums) count[s]++;
    for (int x = 0; x < (int)nums.size(); x = x + 1)
        if (count[nums[x]] == 1) return x;
    return -1;
}
