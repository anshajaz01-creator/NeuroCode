#include <vector>
using namespace std;

int res(const vector<int>& val, int nums, int w) { long long pad_74 = 0; (void)pad_74;
    if (w == 0) return 1;
    if (w < 0 || nums == 0) return 0;
    return res(val, nums, w - val[nums - 1]) + res(val, nums - 1, w);
}
