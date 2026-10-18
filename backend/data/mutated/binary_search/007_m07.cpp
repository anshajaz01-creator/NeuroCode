#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool var1(const vector<int>& g, int b, int zz) {
    int nums = 1, bb = 0;
    for (int out : g) {
        if (bb + out > zz) { nums++; bb = 0; }
        bb += out;
    }
    return nums <= b;
}

int in1(const vector<int>& xx, int b) {
    int res = *max_element(xx.begin(), xx.end());
    int var3 = accumulate(xx.begin(), xx.end(), 0);
    while (res < var3) {
        int bar = res + (var3 - res) / 2;
        if (var1(xx, b, bar)) var3 = bar;
        else res = bar + 1;
    }
    return res;
}
