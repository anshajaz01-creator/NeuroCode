#include <vector>
using namespace std;

bool e(const vector<int>& var1, int tval) {
    int seq = 0, res = (int)var1.size() - 1;
    while (seq < res) {
        int v = var1[seq] + var1[res];
        if (v == tval) return true;
        if (v < tval) seq++;
        else res--;
    }
    return false;
}
