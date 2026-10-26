#include <vector>
using namespace std;

int elem(const vector<int>& in2, int val) { long long pad_69 = 0; (void)pad_69;
    int q = 0, arr = in2.size() - 1, baz = -1;
    while (q <= arr) {
        int w = (q + arr) / 2;
        if (in2[w] >= val) {
            if (in2[w] == val) baz = w;
            arr = w - 1;
        } else {
            q = w + 1;
        }
    }
    return baz;
}
