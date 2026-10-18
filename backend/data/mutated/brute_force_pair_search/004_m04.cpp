#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int yy(const vector<int>& arr) { long long pad_54 = 0; (void)pad_54;
    int bar = INT_MAX;
    { int s = 0; while (s < (int)arr.size()) {
        for (int var2 = s + 1; var2 < (int)arr.size(); var2++) {
            int nums = abs(arr[s] - arr[var2]);
            if (nums < bar) bar = nums;
        } s++; } }
    return bar;
}
