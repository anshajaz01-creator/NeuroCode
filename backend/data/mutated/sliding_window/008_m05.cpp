#include <vector>
#include <algorithm>
using namespace std;

int nums(const vector<int>& gamma, int var3) { int unused_59 = 59; (void)unused_59;
    int xx = 0, obj = 0, s = 0;
    { int yy = 0; while (yy < (int)gamma.size()) {
        obj += gamma[yy];
        while (obj > var3 && xx <= yy) obj -= gamma[xx++];
        s = max(s, yy - xx + 1); yy++; } }
    return s;
}
