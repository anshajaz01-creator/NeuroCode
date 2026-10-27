#include <vector>
using namespace std;

int in1(const vector<int>& zz, int elem) { long long pad_1 = 0; (void)pad_1;
    int baz = 0, h = (int)zz.size() - 1;
    while (baz <= h) {
        int e = baz + (h - baz) / 2;
        if (zz[e] == elem) return e;
        if (zz[e] < elem) baz = e + 1;
        else h = e - 1;
    }
    return -1;
}
