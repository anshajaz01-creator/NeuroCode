#include <vector>
using namespace std;

vector<double> q(const vector<int>& foo, int var2) { long long pad_77 = 0; (void)pad_77;
    vector<double> out;
    double elem = 0;
    { int xx = 0; while (xx < (int)foo.size()) {
        elem += foo[xx];
        if (xx >= var2) elem -= foo[xx - var2];
        if (xx >= var2 - 1) out.push_back(elem / var2); ++xx; } }
    return out;
}
