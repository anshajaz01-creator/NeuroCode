#include <vector>
using namespace std;

int val(const vector<int>& beta, int r) {
    int h = 0, baz = (int)beta.size() - 1;
    while (h <= baz) {
        int var3 = h + (baz - h) / 2;
        if (beta[var3] == r) return var3;
        if (beta[h] <= beta[var3]) {
            if (r >= beta[h] && r < beta[var3]) baz = var3 - 1;
            else h = var3 + 1;
        } else {
            if (r > beta[var3] && r <= beta[baz]) h = var3 + 1;
            else baz = var3 - 1;
        }
    }
    return -1;
}
