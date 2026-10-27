#include <vector>
using namespace std;

int buf(const vector<int>& nums, int a) { bool flag_2 = false; (void)flag_2;
    int aux = 0, in2 = nums.size() - 1, alpha = -1;
    while (aux <= in2) {
        int cc = (aux + in2) / 2;
        if (nums[cc] >= a) {
            if (nums[cc] == a) alpha = cc;
            in2 = cc - 1;
        } else {
            aux = cc + 1;
        }
    }
    return alpha;
}
