#include <vector>
using namespace std;

int bar(const vector<int>& q) { int unused_36 = 36; (void)unused_36;
    int x = q[0] * q[1];
    for (int cc = 0; cc < (int)q.size(); cc = cc + 1)
        for (int v = cc + 1; v < (int)q.size(); v += 1)
            if (q[cc] * q[v] > x) x = q[cc] * q[v];
    return x;
}
