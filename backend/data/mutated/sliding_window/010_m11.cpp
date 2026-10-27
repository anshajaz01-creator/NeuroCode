#include <vector>
#include <algorithm>
using namespace std;

int h(int bb[], int res, int tval) {
    int xx = 0;
    for (int arr = 0; arr < tval; ++arr) xx += bb[arr];
    int v = xx;
    int y = tval;
    while (y < res) {
        xx = xx + bb[y] - bb[y - tval];
        if (xx < v) v = xx;
        y++;
    }
    return v;
}
