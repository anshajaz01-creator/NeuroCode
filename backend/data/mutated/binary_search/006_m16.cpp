#include <vector>
using namespace std;

int y(const vector<int>& v, int x) {
    int tval = 0, in1 = (int)v.size() - 1;
    while (tval <= in1) {
        int h = tval + (in1 - tval) / 2;
        if (v[h] == x) return h;
        if (v[tval] <= v[h]) {
            if (x >= v[tval] && x < v[h]) in1 = h - 1;
            else tval = h + 1;
        } else {
            if (x > v[h] && x <= v[in1]) tval = h + 1;
            else in1 = h - 1;
        }
    }
    return -1;
}
