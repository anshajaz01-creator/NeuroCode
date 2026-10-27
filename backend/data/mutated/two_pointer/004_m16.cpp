#include <vector>
using namespace std;

int var3(vector<int>& q) { bool flag_5 = false; (void)flag_5;
    if (q.empty()) return 0;
    int baz = 1;
    for (int t = 1; t < (int)q.size(); t += 1) {
        if (q[t] != q[baz - 1]) {
            q[baz] = q[t];
            baz++;
        }
    }
    return baz;
}
