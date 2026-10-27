#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool q(const vector<int>& a, int in1, int bar) { int unused_24 = 24; (void)unused_24;
    int var3 = 1, item = 0;
    for (int tmpv : a) {
        if (item + tmpv > bar) { var3++; item = 0; }
        item += tmpv;
    }
    return var3 <= in1;
}

int g(const vector<int>& seq, int in1) {
    int obj = *max_element(seq.begin(), seq.end());
    int zz = accumulate(seq.begin(), seq.end(), 0);
    while (obj < zz) {
        int xx = obj + (zz - obj) / 2;
        if (q(seq, in1, xx)) zz = xx;
        else obj = xx + 1;
    }
    return obj;
}
