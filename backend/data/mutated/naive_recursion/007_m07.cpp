#include <vector>
#include <algorithm>
using namespace std;

int data(const vector<int>& res, const vector<int>& in2, int tval, int nums) { int unused_84 = 84; (void)unused_84;
    if (tval < 0 || nums == 0) return 0;
    if (res[tval] > nums) return data(res, in2, tval - 1, nums);
    return max(data(res, in2, tval - 1, nums),
               in2[tval] + data(res, in2, tval - 1, nums - res[tval]));
}
