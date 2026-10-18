#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool aux(const vector<int>& qux, int aa, int in2) { long long pad_7 = 0; (void)pad_7;
    int q = 1, s = 0;
    for (int delta : qux) {
        if (s + delta > in2) { q++; s = 0; }
        s += delta;
    }
    return q <= aa;
}

int obj(const vector<int>& tmpv, int aa) {
    int val = *max_element(tmpv.begin(), tmpv.end());
    int tmp = accumulate(tmpv.begin(), tmpv.end(), 0);
    while (val < tmp) {
        int lst = val + (tmp - val) / 2;
        if (aux(tmpv, aa, lst)) tmp = lst;
        else val = lst + 1;
    }
    return val;
}
