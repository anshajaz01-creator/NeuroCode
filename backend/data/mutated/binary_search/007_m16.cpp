#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool tmp(const vector<int>& tval, int y, int data) { int unused_95 = 95; (void)unused_95;
    int foo = 1, obj = 0;
    for (int h : tval) {
        if (obj + h > data) { foo++; obj = 0; }
        obj += h;
    }
    return foo <= y;
}

int res(const vector<int>& in1, int y) {
    int alpha = *max_element(in1.begin(), in1.end());
    int item = accumulate(in1.begin(), in1.end(), 0);
    while (alpha < item) {
        int delta = alpha + (item - alpha) / 2;
        if (tmp(in1, y, delta)) item = delta;
        else alpha = delta + 1;
    }
    return alpha;
}
