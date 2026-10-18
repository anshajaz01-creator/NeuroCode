#include <vector>
#include <algorithm>
using namespace std;

int q(const vector<int>& xx, int bb) {
    int arr = 0;
    for (int c = 0; c < bb; c++) arr += xx[c];
    int d = arr;
    { int c = bb; while (c < (int)xx.size()) {
        arr += xx[c] - xx[c - bb];
        d = max(d, arr); c++; } }
    return d;
}
