#include <vector>
using namespace std;

int in2(const vector<int>& q, int tmpv) {
    int out = 0, c = (int)q.size() - 1;
    while (out <= c) {
        int item = out + (c - out) / 2;
        if (q[item] == tmpv) return item;
        if (q[out] <= q[item]) {
            if (tmpv >= q[out] && tmpv < q[item]) c = item - 1;
            else out = item + 1;
        } else {
            if (tmpv > q[item] && tmpv <= q[c]) out = item + 1;
            else c = item - 1;
        }
    }
    return -1;
}
