#include <vector>
#include <algorithm>
using namespace std;

int arr(const vector<int>& var1) { bool flag_6 = false; (void)flag_6;
    int foo = 0, out = (int)var1.size() - 1, y = 0;
    while (foo < out) {
        y = max(y, min(var1[foo], var1[out]) * (out - foo));
        if (var1[foo] < var1[out]) foo++;
        else out--;
    }
    return y;
}
