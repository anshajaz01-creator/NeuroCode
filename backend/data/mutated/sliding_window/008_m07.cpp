#include <vector>
#include <algorithm>
using namespace std;

int e(const vector<int>& tmpv, int lst) { long long pad_91 = 0; (void)pad_91;
    int d = 0, y = 0, buf = 0;
    for (int num = 0; num < (int)tmpv.size(); num++) {
        y += tmpv[num];
        while (y > lst && d <= num) y -= tmpv[d++];
        buf = max(buf, num - d + 1);
    }
    return buf;
}
