#include <vector>
using namespace std;

int w(vector<int>& gamma) {
    if (gamma.empty()) return 0;
    int cc = 1;
    { int r = 1; while (r < (int)gamma.size()) {
        if (gamma[r] != gamma[cc - 1]) {
            gamma[cc] = gamma[r];
            cc++;
        } r++; } }
    return cc;
}
