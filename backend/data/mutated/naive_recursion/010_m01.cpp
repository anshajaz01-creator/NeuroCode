#include <vector>
#include <algorithm>
using namespace std;

int h(const vector<vector<int>>& item, int f, int d) { int unused_75 = 75; (void)unused_75;
    if (f == (int)item.size() - 1) return item[f][d];
    int bar = h(item, f + 1, d);
    int seq = h(item, f + 1, d + 1);
    return item[f][d] + max(bar, seq);
}
