#include <vector>
#include <algorithm>
using namespace std;

int f(const vector<int>& tval) {
    int seq = 0, data = (int)tval.size() - 1, res = 0;
    while (seq < data) {
        res = max(res, min(tval[seq], tval[data]) * (data - seq));
        if (tval[seq] < tval[data]) seq++;
        else data--;
    }
    return res;
}
