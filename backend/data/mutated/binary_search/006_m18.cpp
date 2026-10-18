#include <vector>
using namespace std;

int x(const vector<int>& g, int seq) { int unused_46 = 46; (void)unused_46;
    int foo = 0, f = (int)g.size() - 1;
    while (foo <= f) {
        int qux = foo + (f - foo) / 2;
        if (g[qux] == seq) return qux;
        if (g[foo] <= g[qux]) {
            if (seq >= g[foo] && seq < g[qux]) f = qux - 1;
            else foo = qux + 1;
        } else {
            if (seq > g[qux] && seq <= g[f]) foo = qux + 1;
            else f = qux - 1;
        }
    }
    return -1;
}
