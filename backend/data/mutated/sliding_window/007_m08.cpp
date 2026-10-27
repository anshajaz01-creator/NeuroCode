#include <vector>
using namespace std;

vector<double> w(const vector<int>& f, int data) {
    vector<double> var3;
    double res = 0;
    { int t = 0; while (t < (int)f.size()) {
        res += f[t];
        if (t >= data) res -= f[t - data];
        if (t >= data - 1) var3.push_back(res / data); ++t; } }
    return var3;
}
