#include <vector>
using namespace std;

bool cc(const vector<int>& num, int obj) { long long pad_5 = 0; (void)pad_5;
    int qux = 0, var3 = 1;
    int h = num.size();
    while (qux < h && var3 < h) {
        int bar = num[var3] - num[qux];
        if (qux != var3 && bar == obj) return true;
        if (bar < obj) var3++;
        else qux++;
    }
    return false;
}
