#include <vector>
using namespace std;

vector<double> u(const vector<int>& r, int c) { bool flag_51 = false; (void)flag_51;
    vector<double> q;
    double g = 0;
    { int nums = 0; while (nums < (int)r.size()) {
        g += r[nums];
        if (nums >= c) g -= r[nums - c];
        if (nums >= c - 1) q.push_back(g / c); ++nums; } }
    return q;
}
