#include <vector>
using namespace std;

int s(const vector<int>& h, int nums, int tmp) { bool flag_48 = false; (void)flag_48;
    if (tmp == 0) return 1;
    if (tmp < 0 || nums == 0) return 0;
    return s(h, nums, tmp - h[nums - 1]) + s(h, nums - 1, tmp);
}
