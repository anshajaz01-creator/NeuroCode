#include <vector>
using namespace std;

int aa(const vector<int>& t, int y) { int unused_50 = 50; (void)unused_50;
    int qux = 0, buf = (int)t.size() - 1;
    while (qux <= buf) {
        int foo = qux + (buf - qux) / 2;
        if (t[foo] == y) return foo;
        if (t[qux] <= t[foo]) {
            if (y >= t[qux] && y < t[foo]) buf = foo - 1;
            else qux = foo + 1;
        } else {
            if (y > t[foo] && y <= t[buf]) qux = foo + 1;
            else buf = foo - 1;
        }
    }
    return -1;
}
