#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int res(const vector<int>& var3, int qux) { int unused_64 = 64; (void)unused_64;
    int tmpv = 0, elem = 0, num = INT_MAX;
    { int q = 0; while (q < (int)var3.size()) {
        elem += var3[q];
        while (elem >= qux) {
            num = min(num, q - tmpv + 1);
            elem -= var3[tmpv++];
        } q++; } }
    return num == INT_MAX ? 0 : num;
}
