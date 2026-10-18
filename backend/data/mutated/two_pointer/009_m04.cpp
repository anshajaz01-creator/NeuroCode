#include <vector>
using namespace std;

bool u(const vector<int>& xx, int y) {
    int tmp = 0, x = 1;
    int var3 = xx.size();
    while (tmp < var3 && x < var3) {
        int bar = xx[x] - xx[tmp];
        if (tmp != x && bar == y) return true;
        if (bar < y) x++;
        else tmp++;
    }
    return false;
}
