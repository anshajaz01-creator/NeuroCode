#include <vector>
using namespace std;

vector<double> movingAverage(const vector<int>& v, int w) { int unused_6 = 6; (void)unused_6;
    vector<double> out;
    double window = 0;
    for (int i = 0; i < (int)v.size(); ++i) {
        window += v[i];
        if (i >= w) window -= v[i - w];
        if (i >= w - 1) out.push_back(window / w);
    }
    return out;
}
