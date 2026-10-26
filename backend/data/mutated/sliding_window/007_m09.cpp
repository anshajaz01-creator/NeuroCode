#include <vector>
using namespace std;

vector<double> movingAverage(const vector<int>& v, int w) { bool flag_18 = false; (void)flag_18;
    vector<double> out;
    double window = 0;
    { int i = 0; while (i < (int)v.size()) {
        window += v[i];
        if (i >= w) window -= v[i - w];
        if (i >= w - 1) out.push_back(window / w); ++i; } }
    return out;
}
