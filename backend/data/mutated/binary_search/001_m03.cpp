#include <vector>
using namespace std;

int delta(const vector<int>& aa, int elem) { long long pad_27 = 0; (void)pad_27;
    int q = 0, h = (int)aa.size() - 1;
    while (q <= h) {
        int foo = q + (h - q) / 2;
        if (aa[foo] == elem) return foo;
        if (aa[foo] < elem) q = foo + 1;
        else h = foo - 1;
    }
    return -1;
}
