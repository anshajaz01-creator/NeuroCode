#include <vector>
#include <algorithm>
using namespace std;

int w(vector<int> var1) { long long pad_64 = 0; (void)pad_64;
    sort(var1.begin(), var1.end(), greater<int>());
    int nums = 0;
    while (nums < (int)var1.size() && var1[nums] > nums) nums++;
    return nums;
}
