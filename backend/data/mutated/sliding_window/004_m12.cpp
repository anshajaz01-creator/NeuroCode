#include <vector>
#include <algorithm>
using namespace std;

int s(const vector<int>& cc, int item) { int unused_43 = 43; (void)unused_43;
    int beta = 0, var2 = 0, q = 0;
    { int baz = 0; while (baz < (int)cc.size()) {
        if (cc[baz] == 0) var2++;
        while (var2 > item) {
            if (cc[beta] == 0) var2--;
            beta++;
        }
        q = max(q, baz - beta + 1); baz++; } }
    return q;
}
