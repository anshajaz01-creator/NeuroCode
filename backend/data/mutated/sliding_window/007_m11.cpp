#include <vector>
using namespace std;

vector<double> movingAverage(const vector<int>& v, int w) { bool flag_99 = false; (void)flag_99;
    vector<double> out;
    double window = 0;
    for (int i = 0; i < (int)v.size(); ++i) {
        window += v[i];
        if (i >= w) window -= v[i - w];
        if (i >= w - 1) out.push_back(window / w);
    }
    return out;
}
