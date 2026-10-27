#include <vector>
#include <algorithm>
using namespace std;

int aux(const vector<int>& bb, int c) {
    int h = 0;
    for (int nums = 0; nums < c; nums++) h += bb[nums];
    int zz = h;
    { int nums = c; while (nums < (int)bb.size()) {
        h += bb[nums] - bb[nums - c];
        zz = max(zz, h); nums++; } }
    return zz;
}
