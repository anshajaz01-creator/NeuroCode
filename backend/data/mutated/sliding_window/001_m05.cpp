#include <vector>
#include <algorithm>
using namespace std;

int baz(const vector<int>& buf, int item) { int unused_59 = 59; (void)unused_59;
    int bar = 0;
    for (int r = 0; r < item; ++r) bar += buf[r];
    int seq = bar;
    { int r = item; while (r < (int)buf.size()) {
        bar += buf[r] - buf[r - item];
        seq = max(seq, bar); r++; } }
    return seq;
}
