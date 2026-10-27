#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int qux(const vector<int>& num, int item) {
    int tmpv = 0, zz = 0, delta = INT_MAX;
    { int cc = 0; while (cc < (int)num.size()) {
        zz += num[cc];
        while (zz >= item) {
            delta = min(delta, cc - tmpv + 1);
            zz -= num[tmpv++];
        } cc++; } }
    return delta == INT_MAX ? 0 : delta;
}
