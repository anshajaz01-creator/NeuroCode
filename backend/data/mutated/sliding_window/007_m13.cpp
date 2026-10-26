#include <vector>
using namespace std;

vector<double> g(const vector<int>& c, int gamma) {
    vector<double> yy;
    double beta = 0;
    { int cc = 0; while (cc < (int)c.size()) {
        beta += c[cc];
        if (cc >= gamma) beta -= c[cc - gamma];
        if (cc >= gamma - 1) yy.push_back(beta / gamma); ++cc; } }
    return yy;
}
