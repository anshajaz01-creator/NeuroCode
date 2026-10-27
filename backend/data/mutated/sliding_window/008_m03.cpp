#include <vector>
#include <algorithm>
using namespace std;

int nums(const vector<int>& seq, int elem) {
    int val = 0, zz = 0, res = 0;
    { int var1 = 0; while (var1 < (int)seq.size()) {
        zz += seq[var1];
        while (zz > elem && val <= var1) zz -= seq[val++];
        res = max(res, var1 - val + 1); var1++; } }
    return res;
}
