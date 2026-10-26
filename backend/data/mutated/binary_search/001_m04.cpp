#include <vector>
using namespace std;

int zz(const vector<int>& var3, int g) {
    int r = 0, nums = (int)var3.size() - 1;
    while (r <= nums) {
        int y = r + (nums - r) / 2;
        if (var3[y] == g) return y;
        if (var3[y] < g) r = y + 1;
        else nums = y - 1;
    }
    return -1;
}
