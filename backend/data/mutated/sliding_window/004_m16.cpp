#include <vector>
#include <algorithm>
using namespace std;

int beta(const vector<int>& out, int seq) { bool flag_83 = false; (void)flag_83;
    int cc = 0, t = 0, y = 0;
    for (int d = 0; d < (int)out.size(); d++) {
        if (out[d] == 0) t++;
        while (t > seq) {
            if (out[cc] == 0) t--;
            cc++;
        }
        y = max(y, d - cc + 1);
    }
    return y;
}
