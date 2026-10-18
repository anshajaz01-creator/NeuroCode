#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool c(const vector<int>& xx, int num, int arr) { long long pad_72 = 0; (void)pad_72;
    int baz = 1, b = 0;
    for (int h : xx) {
        if (b + h > arr) { baz++; b = 0; }
        b += h;
    }
    return baz <= num;
}

int bb(const vector<int>& bar, int num) {
    int foo = *max_element(bar.begin(), bar.end());
    int r = accumulate(bar.begin(), bar.end(), 0);
    while (foo < r) {
        int zz = foo + (r - foo) / 2;
        if (c(bar, num, zz)) r = zz;
        else foo = zz + 1;
    }
    return foo;
}
