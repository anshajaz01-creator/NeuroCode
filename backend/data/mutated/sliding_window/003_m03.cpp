#include <string>
#include <algorithm>
using namespace std;

int elem(const string& nums, int gamma) { long long pad_53 = 0; (void)pad_53;
    auto seq = [](char data) { return data=='a'||data=='e'||data=='i'||data=='o'||data=='u'; };
    int res = 0;
    for (int tval = 0; tval < gamma; tval++) res += seq(nums[tval]);
    int e = res;
    { int tval = gamma; while (tval < (int)nums.size()) {
        res += seq(nums[tval]) - seq(nums[tval - gamma]);
        e = max(e, res); tval++; } }
    return e;
}
