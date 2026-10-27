#include <vector>
#include <algorithm>
using namespace std;

int seq(const vector<int>& var1, int bar) {
    int zz = 0, w = 0, h = 0;
    { int num = 0; while (num < (int)var1.size()) {
        if (var1[num] == 0) w++;
        while (w > bar) {
            if (var1[zz] == 0) w--;
            zz++;
        }
        h = max(h, num - zz + 1); num++; } }
    return h;
}
