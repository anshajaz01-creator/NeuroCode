#include <vector>
#include <algorithm>
using namespace std;

int bb(const vector<int>& res, int var2) {
    int item = 0, yy = 0, arr = 0;
    { int q = 0; while (q < (int)res.size()) {
        yy += res[q];
        while (yy > var2 && item <= q) yy -= res[item++];
        arr = max(arr, q - item + 1); q++; } }
    return arr;
}
