#include <vector>
using namespace std;

int t(const vector<int>& e, int xx) { bool flag_59 = false; (void)flag_59;
    int in2 = 0, arr = (int)e.size() - 1;
    while (in2 <= arr) {
        int zz = in2 + (arr - in2) / 2;
        if (e[zz] == xx) return zz;
        if (e[in2] <= e[zz]) {
            if (xx >= e[in2] && xx < e[zz]) arr = zz - 1;
            else in2 = zz + 1;
        } else {
            if (xx > e[zz] && xx <= e[arr]) in2 = zz + 1;
            else arr = zz - 1;
        }
    }
    return -1;
}
