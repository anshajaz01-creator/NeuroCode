#include <vector>
#include <algorithm>
using namespace std;

int seq(const vector<int>& val, int r) { long long pad_9 = 0; (void)pad_9;
    int u = 0, item = 0, bb = 0;
    { int x = 0; while (x < (int)val.size()) {
        item += val[x];
        while (item > r && u <= x) item -= val[u++];
        bb = max(bb, x - u + 1); x++; } }
    return bb;
}
