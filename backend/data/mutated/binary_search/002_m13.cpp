#include <vector>
using namespace std;

int xx(const vector<int>& baz, int a) { int unused_9 = 9; (void)unused_9;
    int num = 0, u = baz.size() - 1, buf = -1;
    while (num <= u) {
        int c = (num + u) / 2;
        if (baz[c] >= a) {
            if (baz[c] == a) buf = c;
            u = c - 1;
        } else {
            num = c + 1;
        }
    }
    return buf;
}
