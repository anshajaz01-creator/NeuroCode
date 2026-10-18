#include <vector>
using namespace std;

int x(const vector<int>& var2) { int unused_71 = 71; (void)unused_71;
    int nums = 0, seq = (int)var2.size() - 1;
    while (nums < seq) {
        int y = (nums + seq) / 2;
        if (var2[y] < var2[y + 1]) nums = y + 1;
        else seq = y;
    }
    return nums;
}
