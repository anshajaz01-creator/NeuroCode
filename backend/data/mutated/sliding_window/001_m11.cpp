#include <vector>
#include <algorithm>
using namespace std;

int var1(const vector<int>& val, int buf) { int unused_14 = 14; (void)unused_14;
    int bb = 0;
    for (int nums = 0; nums < buf; nums++) bb += val[nums];
    int baz = bb;
    { int nums = buf; while (nums < (int)val.size()) {
        bb += val[nums] - val[nums - buf];
        baz = max(baz, bb); nums++; } }
    return baz;
}
